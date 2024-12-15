<?php

namespace admin;

use SQLite3;
use content\content;

/**
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT
 *
 * @link http://hardcopy.free.nf
 * ==================================================================
 *
 *                        admin.class.inc
 *
 * ==================================================================
 * This CCK example site is built around this blogging module.
 * It handles the blog content type
 *
 *
 */
class admin
{
    public $menu;
    public $title = 'Administration';
    public $module;
    public $section;
    public $database = '';


    public function __construct()
    {
        //Test the Common settings
        $this->module = __NAMESPACE__;
        $this->section = __NAMESPACE__;
    }

    /**
     *   Navigation hook for all modules
     */

    public function hook_links()
    {
        $link = 'links';

        $var[$link][1] = array(
                'text' => 'Administration',
                'path' => $this->module . '/main',
                'alias' => 'index',
                'controller' => $this->module,
                'action' => 'main',
                'css_class' => array($this->module, 'main_item'),
                'css_id' => $this->module
                );

        return $var;
    }
    /**
    Permisssion and access hook for per [module]/[method]security check
    */

    public function hook_access()
    {
        $authorize = array(
            $this->module . '/main' => array('access foo'),
            $this->module . '/blocks' => array('access baz'),
            $this->module . '/themes' => array('access boo'),
        );

        return $authorize;
    }

    /**
    *   Sub navigation is a hook and displayed per call by hook_links
    */

    public function hook_module_links($index = 0)
    {

        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Accounts',
                    'path' => $this->module . '/admin_user_accounts',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );

        $var[$link][2] = array(
                    'text' => 'Profiles',
                    'path' => $this->module . '/admin_user_profiles',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );

        $var[$link][3] = array(
                    'text' => 'Categories',
                    'path' => $this->module . '/admin_categories',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                    'text' => 'Content',
                    'path' => $this->module . '/admin_content',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][5] = array(
                    'text' => 'Security',
                    'path' => $this->module . '/admin_permissions',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );
        $var[$link][6] = array(
                    'text' => 'Databases',
                    'path' => $this->module . '/admin_databases',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );
        $var[$link][7] = array(
                    'text' => 'Modules',
                    'path' => $this->module . '/admin_modules',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );
        $var[$link][8] = array(
                'text' => 'Configuration',
                'path' => $this->module . '/admin_config',
                'css_id' => $this->module,
                'css_class' => array($this->module)

        );



        return $var;
    }


    public function main($output = null)
    {
        // get all links from each class controller
        global $cck, $ini_settings, $_SESSION;
        $output = '';
        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');

        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'Login to Site';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );


        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?' .$cck->_path_segment(0). '/' . 'login_check';


        //$output .=  'show message:'. $msg;
        $variables['CCK'] = $cck;
        $variables['content'] = $output ;
        $variables['$POST'] = $_POST;
        $variables['VAR'] = $variables;
        $variables['INI'] = $ini_settings;
        $variables['loggedInUser'] = (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        print $cck->_view('page_admin', $variables);
    }


    public function admin_profiles()
    {
        // get all links from each class controller
        global $cck, $ini_settings;

        $database = $ini_settings['databases']['user_db'];
        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'site admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );


        $variables['contentTitle'] = $cck->_path_segment(1);
        $db = new SQLite3($database);

        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        } else {
            $result = $db->query('SELECT * FROM userlist');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_users_admin', $table);
        $variables['content'] = $output;
        
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);
    }

    public function admin_blogs($is_secure = null)
    {
        // get all links from each class controller
        global $cck, $ini_settings;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = $cck->_path_segment(1);
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );
        $db = new SQLite3($database);

        $result = $db->query('SELECT * FROM blogs');

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_blogs', $table);




        $variables['content'] = 'blog user admin panel' . $output;

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);
    }

    public function admin_databases($is_secure = null)
    {
        // get all links from each class controller
        global $cck, $ini_settings;
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $msg = 'messages : ';

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'Databases';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );
        $db = $ini_settings['databases'];

        $table['header'] = array('name', 'datasource');
        foreach ($db as $alias => $name) {
            $rows[] = array($alias,$name);
        }
        $table['rows'] = $rows;
        $output = $cck->_view('table', $table);

        $variables['content'] = "Databases noted in config.ini file : ". $output;

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);
    }




    public function admin_modules()
    {

        // get all links from each class controller
        global $cck, $ini_settings;
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $msg = 'messages : ';

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'Modules';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );
        $counter = 0;
        $sections = $ini_settings['modules'];
        //var_dump($sections);



        //foreach($section as $name => $value){


        foreach ($sections as $alias => $string) {
            $names = array_keys($sections);
            $table['section'] = 'modules';
            $rows[] = array($alias,$string);


        }





        $table['header'] = array('Action', 'Module','Documentation');
        $table['rows'] = $rows;
        $table['module'] = $rows[1];
        $table['section'] = $sections[1];
        $output = $cck->_view('table_module_ini', $table);

        $variables['content'] = 'configure and admin modules [ <i>config.ini</i>  ]'. $output;

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;

        print $cck->_view('page_admin', $variables);
    }

    /*
     Documentation function  to show developer comments that are to to used
     by end users and developers. Removing the need for documentation that is
     seperate for the site. Future plan is to make it a module rather that a
     group of functions in the admin module
    */
    public function module_comments_view($module = null)
    {

        /* ====================== variables ===============*/
        global $cck,$ini_settings,$_SESSION;
        $variables = array();
        $table = array();
        $output = '';
        $msg = 'messages : ';
        /* ====================== menus ===============*/
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $module = $cck->_path_segment(2);


        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = $module . ' - documentation';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
            'template' => 'links_sub_menu',
            'index' => $this->module,
            'css_id' => $this->module,
            'css_class' => array($this->module)
            ),
            $variables
        );



        if (is_numeric($module)) {
            $module = $ini_settings['modules'][$module];
            $module_class = "\\" . $module."\\". $module;
            $rc = new \ReflectionClass($module_class);
            $table['rows'] = array(array($module, $rc->getDocComment()));
        } elseif (empty($module)) {

            // list modules
            exit('nothing found');

        } else {


            $module_class = "\\" . $module."\\". $module;
            $rc = new \ReflectionClass($module_class);

            //$class_methods = get_class_methods(new myclass());

            $class_methods = get_class_methods($module_class);
            //var_dump($class_methods);
            foreach ($class_methods as $key => $name) {
                $method_comments[] =  $rc->getMethod($name)->getDocComment();
            }
            //exit(var_dump($method_comments));
            $table['otherModules'] = $ini_settings['modules'];
            $table['moduleMethods'] =  $class_methods;
            $table['moduleComments'] = $method_comments;
            $table['rows'] = array(array($module, '<p class="fs-6"><pre style="overflow-x: auto;" class="">'. $rc->getDocComment().'</pre></p>'));

        }

        /* ====================== content ===============*/

        $table['header'] = array( ' Developer comments', 'Methods');

        $table['module'] = $module;
        /* ====================== content template ===============*/
        $output = $cck->_view('table_module_comments', $table);
        $variables['content'] = $output;
        /* ====================== page template ===============*/

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);

    }


    /*
     Documentation function  to show developer comments that are to to used
     by end users and developers. Removing the need for documentation that is
     seperate for the site. Future plan is to make it a module rather that a
     group of functions in the admin module
    */


    public function module_comments($comments_class)
    {

        $get_comments = new ReflectionClass($comments_class);
        return $get_comments->getDocComment();
    }

    public function admin_config()
    {

        // get all links from each class controller
        global $cck, $ini_settings;
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $msg = 'messages : ';

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = $cck->_path_segment(1);
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );
        $counter = 0;
        $sections = array_keys($ini_settings);
        $arguments = array();

        foreach ($sections as $section => $name) {

            //foreach($section as $name => $value){

            if (!is_numeric($section)) {
                //var_dump($ini_settings[$section]);
                $line[$section] = (in_array($ini_settings[$section], $ini_settings) ? $ini_settings[$section] : 'configuration: '.$section.'does not exist');
                $table['line'] = $line;
                $table[$section] = array($section => $name);
                $table['section'] = $section;
                $table['field'] = $name;
                $table['value'] = $line[$section];
            } else {
                //var_dump($ini_settings[$name]);
                $table[$section] = array($section => $name);
                $table['section'] = $section;
                $table['field'] = $name;

                $line[$section] = (in_array($ini_settings[$name], $ini_settings) ? $ini_settings[$name] : 'configuration: '.$name.'does not exist');
                $table['value'] = print_r($line[$section], 1) .'numeric';
                $table['line'] = $line;
            }

            $table['section'] = $name;
            foreach ($ini_settings[$name] as $alias => $string) {
                $rows[] = array($alias,$string, $name);


            }


            $arguments[] = print_r($line, true)."<br>\n";
            $form_qstring = array();


        }
        $table['header'] = array('field', 'data','section');
        $table['rows'] = $rows;
        $output = '<div class="col"'.$cck->_view('table_config_ini', $table).'</div>';

        $variables['content'] = "Config.ini file : ". $output;

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;

        print $cck->_view('page_admin', $variables);
    }



    public function admin_blocks()
    {
        // get all links from each class controller
        global $cck, $ini_settings, $_SESSION;
        // get all links from each class controller
        $output = '';
        $msg = 'messages';
        $table = array();

        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'site admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );




        $variables['content'] = 'main admin panel';

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;

        print $cck->_view('page_admin', $variables);
    }

    public function admin_themes()
    {
        global $cck, $ini_settings, $_SESSION;
        // get all links from each class controller
        $output = '';
        $msg = 'messages : ';
        $table = array();
        $columns = array();
        $rows = array();

        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'site admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );



        $variables['pageTitle'] = $this->title;
        $variables['mainNavigation'] = $cck->_menu_links($main_menu);

        $variables['content'] = 'admin form submit';

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);
    }

    public function admin_content()
    {
        global $cck,$ini_settings,$_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $msg = 'messages : ';

        //some variables to load into the view will appear as $[variable name]
        $output = '';
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $variables['seperators'] = array('|','-',';',':');
        $variables['pageTitle'] = 'Content';
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'Content Admin';
        $variables['contentTitle'] = 'Content Types';
        $variables['dbTable'] = 'content_types';

        //$link = 'links';

        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Content List',
                    'path' => 'admin/content_list',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)

                    );
        $var[$link][2] = array(
                    'text' => 'Content Add',
                    'path' => 'admin/content_add',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Content Permissions',
                    'path' => 'admin/content_permissions',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $admin_menu = $var;
        //$admin_menu = $cck->_hooks('hook_module_links');
        
          

        $db = new SQLite3($database);


        $typeID = $cck->_path_segment(2);
        if (!empty($typeID)) {
            $resultSingle = $db->query('SELECT * FROM content_types WHERE id='.$typeID.'');
        } else {
            $result = $db->query('SELECT * FROM content_types');
        }
        $button_0='';
        $button_1='';
        $field_count = 1;
        $contentTypeForms='';
        $p_rows = array();
        while ($row = $result->fetchArray(SQLITE3_BOTH)) {
            $rows[] = $row;
            $contentTypeName[$row['content_type_id']] = $row['content_type_name'];
            $contentTypeNames[$row['content_type_name']] = $row['content_type_name'];
            $contentTypeIds[$row['content_type_name']] = $row['content_type_id'];
            $resultSingle = $db->query('SELECT * FROM content_types WHERE content_type_id="'.$row['content_type_id'].'"');
            while ($single = $resultSingle->fetchArray(SQLITE3_ASSOC)) {
                $contentTypeInfo[$row['content_type_name']] = $single;
                $table['contentTypeIds'] = '<pre>'.$single['content_type_id'].'-'.$single['content_type_name'].'</pre>';
            }
            
            $resultFields = $db->query('SELECT * FROM content_type_fields WHERE content_type_id="'.$row['content_type_id'].'"');
            while ($tField = $resultFields->fetchArray(SQLITE3_ASSOC)) {
                $contentTypeFields[]= $tField;
                $p_rows[] = $tField;

                $table['contentTypePresentFields'][$row['content_type_name']][$tField['machine_id']] = $tField;
                    
            }

        
            
                $button_1 .= "\n\n\t\t".'<form name="form_type_create_post_with_'.$row['content_type_name'].'" id="form-type-create-post-with-'.$row['content_type_name'].'" class="" method="post">'."\n";
        
                for ($i = 0; $i < $result->numColumns(); $i++) {
                    $col = $result->columnName($i);
                    $columns[] = $col;
                    $button_1 .= "\n".'  <input type="hidden" name="'.$row['content_type_name'].'_fields'.'[available_fields][field_attr]['.$col.']" id="Posted-form-posted-fields-field-attr-'.$col.']" value="'.$col.'" />';
                    //$button_1 .= '<input type="hidden" name="Posted-form[posted-fields][]"  id=""  value="" />'."\n";
                    
                }
                $button_1 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type]" id="Posted-form-posted-content-type-'.$col.'" value="" />';
                $button_1 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type][name]" id="Posted-form-posted-content-type-name-'.$row['content_type_name'].'" value="'.$row['content_type_name'].'" />';
                $button_1 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type][id]" id="Posted-form-posted-content-type-id-'.$row['content_type_id'].'" value="'.$row['content_type_id'].'" />';
                $button_1 .= '<button title="" type="submit" name="create_new_' . $row['content_type_name'] . '" id="post-button-id-'. $row['content_type_id'].'" role="button"  class="btn btn-primary" formaction="?admin/content_type_post/'. $row['content_type_id'] .
                '&content_type_name='.$row['content_type_name'].'">';
                $button_1 .= $row['content_type_name'];
                $button_1 .= '</button>';
                $button_1 .= "\n".'</form>' ."\n";
                $table['contentTypeCreate'] = $button_1;

                $button_0 .= "\n\n\t\t".'<form name="form_type_create_post_with_'.$row['content_type_name'].'" id="form-type-create-post-with-'.$row['content_type_name'].'" class="" method="post">'."\n";
        
                for ($i = 0; $i < $result->numColumns(); $i++) {
                    $col = $result->columnName($i);
                    $columns[] = $col;
                    $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][field_attr]['.$col.']" id="Posted-form-posted-fields-field-attr-'.$col.']" value="'.$col.'" />';
                    //$button_1 .= '<input type="hidden" name="Posted-form[posted-fields][]"  id=""  value="" />'."\n";
                    
                }

                foreach($this->content_type_list($row['content_type_id']) as $fkey => $fvalue){

                    
                    $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields]['.$fkey.']" id="Posted-form-posted-content-type-'.$fkey.'" value="'.$fkey.'" />';
                

                }
                $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type]" id="Posted-form-posted-content-type-'.$col.'" value="" />';
                $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type][name]" id="Posted-form-posted-content-type-name-'.$row['content_type_name'].'" value="'.$row['content_type_name'].'" />';
                $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$row['content_type_name'].'[posted_fields][content_type][id]" id="Posted-form-posted-content-type-id-'.$row['content_type_id'].'" value="'.$row['content_type_id'].'" />';
                $button_0 .= '<button title="" type="submit" name="create_new_' . $row['content_type_name'] . '" id="post-button-id-'. $row['content_type_id'].'" role="button"  class="btn btn-primary" formaction="?admin/content_type_edit/'. $row['content_type_id'] .
                '&content_type_name='.$row['content_type_name'].'">';
                $button_0 .= 'edit';
                $button_0 .= '</button>';
                $button_0 .= "\n".'</form>' ."\n";
                $table['contentTypeEdit'] = $button_0;

               
            
            
        $field_count = $field_count + 1;
        //$table['contentTypePresentFields'][$row['content_type_name']] = $this->content_type_list($row['content_type_id']);
       
}
        
        //$contentTypeForms = $cck->_view('form_content_type_edit', $form);
    

        //SQLite3Result::numColumns();

        $table['header'] = $columns;
        $table['rows'] = $rows;
        $table['contentTypeInfo'] = $contentTypeInfo;
        $table['contentTypeNames'] = $contentTypeNames;
        $table['contentTypeFields'] = $contentTypeFields;
        
        
        $output .= $cck->_view('table_content_types_admin', $table);
        
        

        foreach ($rows as $key => $value) {
            $variables['userBio'] =  '';
            $variables['userName'] = '';
            $variables['profileImage'] = '';
            $variables['userID'] = '';
        }
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $variables['content'] = $output;

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);

    }


    public function admin_content_field_add()
    {

        global $cck,$ini_settings,$_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $form = array();
        $columns = array();
        $rows = array();
        $table = array();
        $output = '';
        $msg = 'messages : ';

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'Add Field to - <i>'. $_POST['content_type'].'</i>';
        $variables['pageTitle'] = 'Admin - Content Types';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);

        //$link = 'links';
        $userID = $cck->_path_segment(2);

        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_class' => array($this->module, 'sub_item'),
                'css_id' => $this->module
                ),
            $variables
        );


        $db = new SQLite3($database);

        $typeID = $cck->_path_segment(2);

        $resultAdd = $db->query('SELECT * FROM content_types WHERE type_id ="'. $typeID.'";');
        $result = $db->query('SELECT * FROM content_type_fields WHERE content_type_id ="'. $typeID.'" ORDER BY weight asc;');

        while ($row = $result->fetchArray()) {
            $rows[] = $row;

        }


        while ($rowAdd = $resultAdd->fetchArray()) {
            $form['contentType'] = $rowAdd['name'];
            $form['contentTypeId'] = $rowAdd['id'];

            $r[] = $rowAdd;
        }
        //var_dump($rows);
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[$col] = $col;
        }
        $form_element_types = array(

            'input' => 'input',
            'textarea' => 'textarea',
            'radio' => 'radio',
            'select' => 'select',
            'checkbox' => 'checkbox',
            'date' => 'date',
            'date-time' => 'datetime-local',
            'email' => 'email',
            'file' => 'file',
            'hidden' => 'hidden',
            'image' => 'image',
            'month' => 'month',
            'week' => 'week',
            'number' => 'number',
            'password' => 'password',
            'range' => 'range',
            'reset' => 'reset',
            'search' => 'search',
            'submit' => 'submit',
            'text' => 'text',
            'time' => 'time',
            'url' => 'url',
            'color' => 'color'
            );
        $form['elementTypes'] = $form_element_types;
        $form['formAction'] = '?content/content_post_save/'. $form['contentType'];
        $form['mimeType'] = '';
        $form['header'] = $columns;
        $form['rows'] = $rows;

        $form['contentUserId'] = (isset($form['contentUserId']) ? $form['contentUserId'] : '1');
        $form['userName'] = (isset($form['userName']) ? $form['userName'] : 'owner');
        $form['contentType'] = (isset($form['contentType']) ? $form['contentType'] : '');
        $form['contentId'] = $form['contentType'].'-'.hash('crc32', $cck->_path_segment(1).time() . mt_rand()) .'-'. $form['userName'];
        $form['contentTime'] = date("Y-m-d H:i:s");
        $output = $cck->_view('form_content_field_add', $form);



        $variables['content'] = 'Add new field to - <h3><i>'.$form['contentType'].'</i></h3>' . $output;
        
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin_form', $variables);

    }

    public function admin_categories()
    {
        // get all links from each class controller
        global $cck,$ini_settings,$_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $msg = 'messages . ';
        $output = '';

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'Categories';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );
        $db = new SQLite3($database);

        $result = $db->query('SELECT * FROM categories');

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_categories', $table);



        $variables['content'] = 'categories admin panel' . $output;
        
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
       
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);
    }

    public function admin_users($is_secure = true)
    {
        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';



        //$link = 'links';
        $userID = $cck->_path_segment(2);
        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Profile',
                    'path' => 'admin/admin_user_profiles/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Account',
                    'path' => 'admin/admin_user_accounts/' . $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Content',
                    'path' => 'admin/admin_user_content/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                    'text' => 'Settings',
                    'path' => 'admin/admin_user_settings/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                    'text' => 'Inbox',
                    'path' => 'admin/admin_user_messages/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);



        $variables['contentTitle'] = $cck->_path_segment(1);
        $db = new SQLite3($database);

        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        } else {
            $result = $db->query('SELECT * FROM userlist');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_users_admin', $table);
        $variables['content'] = $output;
        
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);
    }

    public function admin_user_content($userID = null)
    {


        global $cck,$ini_settings,$_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'admin user content';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);

        //$link = 'links';
        $userID = $cck->_path_segment(2);
        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Profile',
                    'path' => 'admin/admin_user_profiles/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Account',
                    'path' => 'admin/admin_user_accounts/' . $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Content',
                    'path' => 'admin/admin_user_content/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                    'text' => 'Settings',
                    'path' => 'admin/edit_user_settings/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                    'text' => 'Inbox',
                    'path' => 'admin/admin_user_messages/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $db = new SQLite3($database);

        $result = $db->query('SELECT * FROM categories');

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_categories', $table);


        $variables['CCK'] = $cck;
        $variables['content'] = 'admin  user_error content panel' . $output;

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);
    }

    public function admin_user_profiles($userID = null)
    {
        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

        /// build admin navigation links that only are used by this module/method


        //$link = 'links';
        $userID = $cck->_path_segment(2);
        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Profiles',
                    'path' => 'admin/admin_user_profiles/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Accounts',
                    'path' => 'admin/admin_user_settings/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
                    $var[$link][2] = array(
                        'text' => 'Permissions',
                        'path' => 'admin/admin_permissions/'.$userID,
                        'css_id' => $this->module,
                    'css_class' => array($this->module)
                        );
        $var[$link][3] = array(
                    'text' => 'Content',
                    'path' => 'admin/admin_user_content/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'Inboxes',
                'path' => 'admin/admin_user_messages/' .$userID,
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $variables['contentTitle'] = 'User Profiles';
        $db = new SQLite3($database);

        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        } else {
            $result = $db->query('SELECT * FROM userlist');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_user_edit_admin', $table);

        foreach ($rows as $key => $value) {
            $variables['userBio'] =  $value['bio'];
            $variables['userName'] = $value['name'];
            $variables['profileImage'] = $value['image'];
            $variables['userID'] = $userID;
        }
        
        

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);

    }

    public function admin_user_accounts($userID = null)
    {
        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg ='messages : ';

        /// build admin navigation links that only are used by this module/method


        //$link = 'links';
        $userID = '0';
        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Profiles',
                    'path' => 'admin/admin_user_profiles/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Accounts',
                    'path' => 'admin/admin_user_settings/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
                    $var[$link][3] = array(
                        'text' => 'Permissions',
                        'path' => 'admin/admin_permissions/'.$userID,
                        'css_id' => $this->module,
                    'css_class' => array($this->module)
                        );
        $var[$link][4] = array(
                    'text' => 'Content',
                    'path' => 'admin/admin_user_content/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][5] = array(
                'text' => 'Inboxes',
                'path' => 'admin/admin_user_messages/' .$userID,
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $variables['contentTitle'] = 'User Accounts';
        $db = new SQLite3($database);

        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        } else {
            $result = $db->query('SELECT * FROM userlist');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_user_edit', $table);

        foreach ($rows as $key => $value) {
            $variables['userBio'] =  $value['bio'];
            $variables['userName'] = $value['name'];
            $variables['profileImage'] = $value['image'];
            $variables['userID'] = $userID;
        }
    

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;

        print $cck->_view('page_admin', $variables);

    }

    public function admin_user_settings($userID = null)
    {



        global $cck,$ini_settings,$_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $msg = 'mesages : ';

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'admin user settings';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module
                ),
            $variables
        );
        $db = new SQLite3($database);

        $result = $db->query('SELECT * FROM categories');

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_categories', $table);

        $variables['content'] = 'admin user settings panel' . $output;
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;

        print $cck->_view('page_admin', $variables);
    }

    public function admin_user_messages($uderID = null)
    {


        global $cck,$ini_settings,$_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'admin user messages';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => '-'. $this->module,
                'css_name' => array($this->module)
                ),
            $variables
        );
        $db = new SQLite3($database);

        $result = $db->query('SELECT * FROM categories');

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_categories', $table);


        $variables['CCK'] = $cck;
        $variables['content'] = 'user messages admin panel' . $output;

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);


    }

    public function admin_permissions()
    {

        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg ='mesages : ';

        /// build admin navigation links that only are used by this module/method


        //$link = 'links';

        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Permissions',
                    'path' => 'admin/admin_permissions',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)

                    );
        /**$var[$link][2] = array(
                    'text' => 'Your Account',
                    'path' => 'users/user_account'
                    );
        $var[$link][3] = array(
                    'text' => 'Your Content',
                    'path' => 'users/user_blog'
                    );
        $var[$link][4] = array(
                'text' => 'User settings',
                'path' => 'users/user_settings'
        );
        $var[$link][5] = array(
                'text' => 'Your Inbox',
                'path' => 'users/user_messages'
        */



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Security';
        $variables['adminMenuTitle'] = 'User Security';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);




        $variables['contentTitle'] = 'User Permissions';
        $db = new SQLite3($database);

        $result = $db->query('SELECT * FROM user_permissions');

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_users', $table);
        $variables['CCK'] = $cck;
        $variables['content'] = $output;

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);
    }


    public function admin_config_edit()
    {
        $link = 'links';


        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $var = array();
        $output = '';
        $msg = 'messages : ';


        $var = array();

        $var[$link][1] = array(
                    'text' => 'User Profile',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'User Accounts',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'User Content',
                    'path' => 'blog/blog_user',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'User Settings',
                'path' => 'users/user_settings',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $sub_menu = $cck->_hooks('hook_module_links');
        $menu = $cck->_hooks('hook_links');
        $admin_menu = $var;


        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Edit Site Configuration';
        $variables['contentTitle'] = 'Edit';
        $variables['userBio'] = 'thanks for the updated information';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);
        parse_str($_SERVER['QUERY_STRING'], $qstring);
        $counter = 0;
        $arguments = '';
        $action_prep = '';
        foreach ($qstring as $section => $field) {

            if ($counter > 0) {
                $line[$section] = (in_array($ini_settings[$section], $ini_settings) ? $ini_settings[$section] : 'configuration: '.$section.'does not exist');
                $form[$section] = array($section => $field);
                $form['line'] = $line;
                $form['section'] = $section;
                $form['field'] = $field;
                $form['value'] = $line[$section];
                $arguments .= print_r($line, true)."<br>\n";
                $action_prep .= '&'.$section.'=' . $field;
            }

            $counter = $counter + 1;
        }
        $output .= '<div class="row"><div class="col"><h3>Present configuration</h3><pre>'. print_r($this->build_ini_string($line), true).'</pre>';
        $output .= '<pre>'.$arguments. '</pre></div>';
        $output .= '<div class="col"><h3>Make changes</h3>';
        //make form from array
        $form['formAction'] = '?admin/config_ini_save'.$action_prep;

        $form['content'] =  $output;
        $form['form'] = array($output. '<pre>' . print_r($form, true). '</pre>');
        $output .=  $cck->_view('form_config_ini_update', $form). '</div></div>';
        $variables['CCK'] = $cck;
        $variables['content'] =  $output;

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);

    }
    /*
    *  Save the new settings to new file rename old to back-up status
    */
    public function config_ini_save()
    {
        $link = 'links';


        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $var = array();
        $output = '';
        $msg = 'messages : ';


        $var = array();

        $var[$link][1] = array(
                    'text' => 'User Profile',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'User Accounts',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'User Content',
                    'path' => 'blog/blog_user',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'User Settings',
                'path' => 'users/user_settings',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $sub_menu = $cck->_hooks('hook_module_links');
        $menu = $cck->_hooks('hook_links');
        $admin_menu = $var;


        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Edit Site Configuration';
        $variables['contentTitle'] = 'New Configuration Saved';
        $variables['userBio'] = 'thanks for the updated information';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);
        parse_str($_SERVER['QUERY_STRING'], $qstring);
        $counter = 0;
        $arguments = '';
        foreach ($qstring as $section => $field) {

            if ($counter > 0) {
                $line[$section] = (in_array(isset($ini_settings[$section]), $ini_settings) ? $ini_settings[$section] : array('configuration: ['.$section.'] does not exist'));
                $form[$section] = array($section => $field);
                $form['line'] = $line;
                $form['section'] = $section;
                $form['field'] = $field;
                $form['value'] = $line[$section];
                $arguments .= print_r($line, true)."<br>\n";
                $form_qstring = array();
            }
            $counter = $counter + 1;
        }

        $output .= '<div class="row"><div class="col"><h3>Old configuration</h3><pre>'. print_r($this->build_ini_string($line), true).'</pre>';
        $output .= '<pre>'.$arguments. '</pre></div>';
        $output .= '<div class="col"><h3>Changes Saved</h3><pre>'. print_r($_POST, 1) . print_r($qstring, 1).'</pre>';
        //make form from array
        $form['formAction'] = '?admin/admin_config_save&'.$form['section'] . '=' . $form['field'];

        $form['content'] =  $output;
        $form['form'] = array($output. '<pre>' . print_r($form, true). '</pre>');
        // no form on save $output .=  $cck->_view('form_config_ini_save', $form );
        //$output .= $output. '<pre>' . print_r($_POST, TRUE). '</pre>';
        $output .= '</div></div>';
        
        

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);

    }
    /**
     * Write array to new ini format
     *
     */
    public function build_ini_string(array $a)
    {
        $out = '';
        $sectionless = '';
        foreach ($a as $rootkey => $rootvalue) {
            if (is_array($rootvalue)) {
                // find out if the root-level item is an indexed or associative array
                $indexed_root = array_keys($rootvalue) == range(0, count($rootvalue) - 1);
                // associative arrays at the root level have a section heading
                if (!$indexed_root) {
                    $out .= PHP_EOL."[$rootkey]".PHP_EOL;
                }
                // loop through items under a section heading
                foreach ($rootvalue as $key => $value) {
                    if (is_array($value)) {
                        // indexed arrays under a section heading will have their key omitted
                        $indexed_item = array_keys($value) == range(0, count($value) - 1);
                        foreach ($value as $subkey => $subvalue) {
                            // omit subkey for indexed arrays
                            if ($indexed_item) {
                                $subkey = "";
                            }
                            // add this line under the section heading
                            $out .= "{$key}[$subkey] = $subvalue" . PHP_EOL;
                        }
                    } else {
                        if ($indexed_root) {
                            // root level indexed array becomes sectionless
                            $sectionless .= "{$rootkey}[] = $value" . PHP_EOL;
                        } else {
                            // plain values within root level sections
                            $out .= "$key = $value" . PHP_EOL;
                        }
                    }
                }

            } else {
                // root level sectionless values
                $sectionless .= "$rootkey = $rootvalue" . PHP_EOL;
            }
        }
        return $sectionless.$out;
    }

    public function login_user($is_secure = true)
    {
        $link = 'links';


        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $var = array();
        $output = '';
        $msg = 'messages: ';


        $var = array();

        $var[$link][1] = array(
                    'text' => 'User Profile',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'User Accounts',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'User Content',
                    'path' => 'blog/blog_user',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                    'text' => 'User Settings',
                    'path' => 'users/user_settings',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );



        $sub_menu = $cck->_hooks('hook_module_links');
        $menu = $cck->_hooks('hook_links');
        $admin_menu = $var;


        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'User Login';
        $variables['contentTitle'] = 'user log in';
        $variables['userBio'] = '';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);
        

        /** check for user */
        $user_check = function ($username, $password) {
            global $cck,$ini_settings,$_SESSION;
            $user_list = array_keys($ini_settings['Users']['UserData']);
            if (in_array($username, $user_list)) {
                $line = "\n";
                $line .= 'User:'. $username. ' <span style="font-weight:600; color:green;text-decoration:underline">found</span> checking password ....'."\n";
                if ($password == $ini_settings['Users']['UserData'][$username]) {

                    $line .= 'Password: password ok <span style="font-weight:600;color: green;text-decoration:underline">access granted</span>';

                } else {
                    $line .= 'Could not login with password: '. $password;
                }
                return $line;
            } else {
                return $user_list;


            }

        };

        $_SESSION['UserData']['UserName'] = isset($_POST['Username']) ? $_POST['Username'] : 'no name given';
        $_SESSION['UserData']['Password'] = isset($_POST['Password']) ? $_POST['Password'] : 'no password given';
        $_SESSION['UserData']['OpenSession'] = isset($_POST['open_session']) ? $_POST['open_session'] : 'go to login page';


        //$msg = "<span style='color:red'>Invalid Login Details</span>";
        $output .= '<pre>';
        if (isset($_POST['Username']) and isset($_POST['Password'])) {
            $output .=  'CHECK CREDENTIALS:'. print_r($user_check($_POST['Username'], $_POST['Password']), 1);
        }
        $output .= '<hr>POST:'.print_r($_POST, 1).'<hr>SESSION:'.print_r($_SESSION, 1).
        '<hr>USERS:'.print_r($ini_settings['Users'], 1).
        '</pre>';//$cck->_view('forms_admin_login', $variables);

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_user_login', $variables);


    }

    public function login_check($is_secure = true)
    {
        $link = 'links';


        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $var = array();
        $output = '';
        $msg = 'messages: ';


        $var = array();

        $var[$link][1] = array(
                    'text' => 'User Profile',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'User Accounts',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'User Content',
                    'path' => 'blog/blog_user',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                    'text' => 'User Settings',
                    'path' => 'users/user_settings',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );



        $sub_menu = $cck->_hooks('hook_module_links');
        $menu = $cck->_hooks('hook_links');
        $admin_menu = $var;


        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'User Login';
        $variables['contentTitle'] = 'user log in';
        $variables['userBio'] = '';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);
        $variables['CCK'] = $cck;

        /** check for user */
        $user_check = function ($username, $password) {
            global $cck,$ini_settings,$_SESSION;
            $user_list = array_keys($ini_settings['Users']['UserData']);

            
            if (in_array($username, $user_list) and isset($_POST['Username']) and isset($_POST['Password'])) {
                $line = "\n";
                $line .= 'User:'. $username. ' <span style="font-weight:600; color:green;text-decoration:underline">found</span> checking password ....'."\n";
                if ($password == $ini_settings['Users']['UserData'][$username]) {

                    $line .= 'Password: password ok <span style="font-weight:600;color: green;text-decoration:underline">access granted</span>';
                    
                    $_SESSION['UserData']['approved'] = (in_array($username, $user_list) ? $username : 'Guest');

                } else {
                    $line .= 'Could not login with password: '. $password;
                }
                return $line;
            } else {
                
                $line = '<div style="position:relative;height:40px;"><span id="user-warning-0" style="top:6px;position:absolute;z-index:1000;border: solid red 2px; color:red;background-color:#efd2d2;padding: 2px 5px 2px 5px;"> User not in Site Admin list!!</span></div><hr>';
                $line.= 'USERS WITH CREDENTIALS:'. print_r($user_list,1);
                $_SESSION['UserData']['approved'] = (!in_array($username, $user_list) ? 'Guest' : $username);
                return $line;


            }

        };

        /* connect to user database profile via unique email address */
        $variables['contentTitle'] = 'Login Check';
        $db = new SQLite3($database);

        $userID = isset($_POST['Username']) ? $_POST['Username'] : 'carl@dev.com';
        if (!empty($userID)) {
            $result = $db->query('SELECT id,email,alias,user_id FROM userlist WHERE email=\''.$userID.'\'');
            //$numRows = $result->numRows();
        } else {
            exit('User input error!');
        }

        while ($row = $result->fetchArray(SQLITE3_ASSOC)) 
        {
            
                //$col = $result->columnName($i);
                $_SESSION['UserData']['inDatabase'] = '<pre style="max-width: 400px;word-wrap: break-all;">'.print_r($row,1).'</pre>';
                
                foreach($row as $key => $value)
                {
                    $_SESSION['UserData'][$key] = $value;

                }
            
            
        }
        
        //exit('<pre>'. print_r($_POST,1). print_r($_SESSION,1).'</pre>' );
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        //$output .= $cck->_view('table_profile_edit', $table);
       

        $_SESSION['UserData']['UserName'] = isset($_POST['Username']) ? $_POST['Username'] : 'Guest';
        $_SESSION['UserData']['Password'] = isset($_POST['Password']) ? $_POST['Password'] : 'no password';
        $_SESSION['UserData']['LoginPage'] = isset($_POST['redirect_back']) ? $_POST['redirect_back'] : $ini_settings['url']['frontpage'];
        $_SESSION['UserData']['OpenSession'] = isset($_POST['open_session']) ? $_POST['open_session'] : 'online';
       // $_SESSION['UserData']['Profile'] = print_r(print_r($rows,1),1);

       if(!isset($_POST)){

        $_POST['error'] = 'no form sent';

       }

        
        //$msg = "<span style='color:red'>Invalid Login Details</span>";
        $user = (isset($_POST['Username']) ? $_POST['Username'] : 'carl@dev.com');
        $pass = (isset($_POST['Password']) ? $_POST['Password'] : '123456');
        $return = (isset($_POST['redirect_back']) ? $_POST['redirect_back'] : '123456');
        
        $output .=  '<pre>'. print_r($user_check($user, $pass), 1).
        '<hr>POSTED CREDENTIALS:'.print_r($_POST, 1).'<hr>SESSION PROFILE:'.print_r($_SESSION, 1).
        '<hr>ALL USERS:'.print_r($ini_settings['Users'], 1).

        '</pre>';//$cck->_view('forms_admin_login', $variables);
   $variables['content'] =  '<div style="text-align : center;"><a class="btn btn-primary" role="button" href="'.$return.'"> Go back to page</a>'.
        '</div>'. $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);


    }

    public function logout_user()
    {
        global $cck,$ini_settings,$_SESSION;
        //$output = print_r($_POST,1);
        $url = (isset($POST['redirect_back']) ? $_POST['redirect_back'] : 'http://' . $_SERVER['HTTP_HOST'] . $ini_settings['url']['frontpage'] );
        //$url .= '<pre>'.print_r($_POST,1).'</pre>';
        session_destroy();
        //exit('http://' . $url);
        header('location:'. $_POST['redirect_back'] .'');
       
    }

    public function edit_profile($userID = null)
    {
        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

        /// build admin navigation links that only are used by this module/method


        //$link = 'links';
        $userID = $cck->_path_segment(2);
        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Profile',
                    'path' => 'admin/edit_profile/'.$userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Account',
                    'path' => 'admin/edit_user/'.$userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Content',
                    'path' => 'admin/edit_post/'.$userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                    'text' => 'Settings',
                    'path' => 'admin/edit_user_settings/'.$userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                    'text' => 'Inbox',
                    'path' => 'admin/edit_messages/' .$userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $variables['contentTitle'] = $cck->_path_segment(1);
        $db = new SQLite3($database);

        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        } else {
            $result = $db->query('SELECT * FROM userlist');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_user_edit', $table);

        foreach ($rows as $key => $value) {
            $variables['userBio'] =  $value['bio'];
            $variables['userName'] = $value['name'];
            $variables['profileImage'] = $value['image'];
            $variables['userID'] = $userID;
        }

        

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;

        print $cck->_view('page_profile', $variables);

    }



    public function edit_user($userID = null)
    {
        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

        /// build admin navigation links that only are used by this module/method


        //$link = 'links';
        $userID = $cck->_path_segment(2);
        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Profile',
                    'path' => 'admin/edit_profile/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Account',
                    'path' => 'admin/edit_user/' . $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Your Content',
                    'path' => 'admin/edit_post/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                    'text' => 'Settings',
                    'path' => 'admin/edit_user_settings/'. $userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                    'text' => 'Inbox',
                    'path' => 'admin/edit_messages/'. $userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $variables['contentTitle'] = $cck->_path_segment(1);
        $db = new SQLite3($database);

        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        } else {
            $result = $db->query('SELECT * FROM userlist');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_user_edit', $table);

        foreach ($rows as $key => $value) {
            $variables['userBio'] =  $value['bio'];
            $variables['userName'] = $value['name'];
            $variables['profileImage'] = $value['image'];
            $variables['userID'] = $userID;
        }
        
        

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_profile', $variables);

    }

    public function edit_user_save()
    {
        $link = 'links';


        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $var = array();
        $output = '';
        $msg = 'messages : ';



        $var = array();

        $var[$link][1] = array(
                    'text' => 'User Profile',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'User Accounts',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'User Content',
                    'path' => 'blog/blog_user',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'User Settings',
                'path' => 'users/user_settings',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $sub_menu = $cck->_hooks('hook_module_links');
        $menu = $cck->_hooks('hook_links');
        $admin_menu = $var;


        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'User account saved';
        $variables['contentTitle'] = 'account saved';
        $variables['userBio'] = 'thanks for the updated information';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);
        $output = $cck->_target('form_post');
        
        
        
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_user_save', $variables);

    }


    public function edit_profile_save()
    {
        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $var = array();
        $output = '';
        $msg = 'messages : ';


        $link = 'links';


        $var = array();

        $var[$link][1] = array(
                    'text' => 'User Profile',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'User Accounts',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'User Content',
                    'path' => 'blog/blog_user',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'User Settings',
                'path' => 'users/user_settings',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $sub_menu = $cck->_hooks('hook_module_links');
        $menu = $cck->_hooks('hook_links');
        $admin_menu = $var;


        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $output .= $cck->_target('form_post');

        

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;

        print $cck->_view('page_user_save', $variables);

    }

    public function edit_category($userID = null)
    {
        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';


        /// build admin navigation links that only are used by this module/method


        //$link = 'links';

        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Your Profile',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Your Account',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Your Content',
                    'path' => 'users/user_content',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'User settings',
                'path' => 'users/user_settings',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                'text' => 'Your Inbox',
                'path' => 'users/user_messages',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $variables['contentTitle'] = $cck->_path_segment(1);
        $db = new SQLite3($database);

        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        } else {
            $result = $db->query('SELECT * FROM userlist');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table', $table);

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);

    }


    public function edit_post($userID = null)
    {
        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';


        /// build admin navigation links that only are used by this module/method


        //$link = 'links';

        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Your Profile',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Your Account',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Your Content',
                    'path' => 'users/user_content',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                    'text' => 'User settings',
                    'path' => 'users/user_settings',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                'text' => 'Your Inbox',
                'path' => 'users/user_messages',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $variables['contentTitle'] = $cck->_path_segment(1);
        $db = new SQLite3($database);

        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        } else {
            $result = $db->query('SELECT * FROM userlist');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $table['CCK'] = $cck;
        $table['INI'] = $ini_settings;
        $output = $cck->_view('table', $table);

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);

    }


    public function edit_config($userID = null)
    {
        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';


        /// build admin navigation links that only are used by this module/method


        //$link = 'links';

        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Your Profile',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Your Account',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Your Content',
                    'path' => 'users/user_content',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'User settings',
                'path' => 'users/user_settings',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                'text' => 'Your Inbox',
                'path' => 'users/user_messages',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $variables['contentTitle'] = $cck->_path_segment(1);
        $db = new SQLite3($database);

        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        } else {
            $result = $db->query('SELECT * FROM userlist');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $table['CCK'] = $cck;
        $table['INI'] = $ini_settings;
        $output = $cck->_view('table', $table);

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);

    }


    public function user_profiles($userID = null)
    {
        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';


        /// build admin navigation links that only are used by this module/method


        //$link = 'links';

        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Your Profile',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Your Account',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Your Content',
                    'path' => 'users/user_content',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'User settings',
                'path' => 'users/user_settings',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                'text' => 'Your Inbox',
                'path' => 'users/user_messages',
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $variables['contentTitle'] = $cck->_path_segment(1);
        $db = new SQLite3($database);

        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT * FROM userlist WHERE id='.$userID.'');
        } else {
            $result = $db->query('SELECT * FROM userlist');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $table['CCK'] = $cck;
        $table['INI'] = $ini_settings;
        $output = $cck->_view('table', $table);

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);

    }

    function content_type_list($listID)
    {

        global $cck,$ini_settings, $_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';


        $db = new SQLite3($database);
        $count = 1;
        $button_0 = '';
        $type_forms = '';

            $result = $db->query('SELECT * FROM content_type_fields WHERE content_type_id ="'. $listID.'" ORDER BY weight asc;');

            $number_of_rows = 0;//for now

            while($row = $result->fetchArray()) {
                $number_of_rows += 1;
            }
        if($number_of_rows < 2){

            $button_0 = "\n\n\t\t".'<form name="form_field_name" id="form-field-id" class="" method="post">'."\n";
                
                    
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.'[posted_fields][content_type]" id="Posted-form-posted-content-type-" value="" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.'[posted_fields][content_type][name]" id="Posted-form-posted-content-type-name-" value="" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.'[posted_fields][content_type][id]" id="Posted-form-posted-content-type-id-" value="" />';
                        $button_0 .= '<button title="" type="submit" name="add_new_field" id="" role="button"  class="btn btn-primary" formaction="?admin/content_type_edit/"'.$listID.'>';
                        $button_0 .= 'add field';
                        $button_0 .= '</button>';
                        $button_0 .= "\n".'</form>' ."\n";
                        $rows = array('message' => 'no fields found');

        }else{
                while ($row = $result->fetchArray(SQLITE3_ASSOC)) {
                        $rows[$row['field_type'].'-'. $row['name'].'-'. $row['machine_id']] = $row;
                        $get_name = $db->querySingle('SELECT * FROM content_types WHERE content_type_id='.$row['content_type_id'], true);
                        //var_dump($get_name);
                        $button_add='';
                        $button_0 .= "\n\n\t\t".'<form name="form_field_name_'.$row['name'].'" id="form-field-id-'.$row['machine_id'].'" class="" method="post">'."\n";
                        
                            for ($i = 0; $i < $result->numColumns(); $i++) {
                                $col = $result->columnName($i);
                                $columns[] = $col;
                                $button_0 .= "\n".'  <input type="hidden" name="'.$get_name['content_type_name'].'_fields'.'['.$row['machine_id'].'][available_fields]['.$row['machine_id'].'][field_attr]['.$col.']" id="Posted-form-posted-fields-field-attr-'.$col.']" value="'.$col.'" />';
                                //$button_1 .= '<input type="hidden" name="Posted-form[posted-fields][]"  id=""  value="" />'."\n";
                                
                            }
                        
                        foreach($result as $list_key => $list_value) {
                                
                                $button_add .= "\n".'  <input type="hidden" name="'.$get_name['content_type_name'].'_fields'.'['.$list_key['machine_id'].'][type_fields]['.$row['machine_id'].'][field_attr]['.$col.']" id="Posted-form-posted-fields-field-attr-'.$col.']" value="'.$col.'" />';
                                
                                
                        }
                        $button_0 .= $button_add;
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][machine_id]" id="Posted-form-posted-content-type-field-options-list" value="'.$row['machine_id'].'" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][html_tag]" id="Posted-form-posted-content-type-field-html-tag" value="'.$row['html_tag'].'" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][html_role]" id="Posted-form-posted-content-type-field-options-html-role" value="'.$row['html_role'].'" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][placeholder]" id="Posted-form-posted-content-type-field-placeholder" value="'.$row['placeholder'].'" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][descrption]" id="Posted-form-posted-content-type-field-description" value="'.$row['description'].'" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][label]" id="Posted-form-posted-content-type-field-label" value="'.$row['label'].'" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][value]" id="Posted-form-posted-content-type-field-value" value="'.$row['value'].'" />';
                       
                       
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][field_options_id]" id="Posted-form-posted-content-type-field-options-list" value="'.$row['option_list_id'].'" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][field_type]" id="Posted-form-posted-content-type-field-type" value="'.$row['field_type'].'" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][field_name]" id="Posted-form-posted-content-type-field-name'.
                        $row['content_type_id'].'" value="'.$get_name['content_type_name'].'" />';
                        $button_0 .= "\n".'  <input type="hidden" name="Posted_'.$get_name['content_type_name'].'[content_field]['.$row['machine_id'].'][field_id]" id="Posted-form-posted-content-type-id-'.$row['content_type_id'].'" value="'.$row['content_type_id'].'" />';
                        $button_0 .= '<button title="" type="submit" name="create_new_' . $get_name['content_type_name'] . '" id="post-button-id-'. $row['content_type_id'].'" role="button"  class="btn btn-primary" formaction="?admin/content_type_edit/'. $row['content_type_id'] .
                        '&content_type_name='.$get_name['content_type_name'].'&content_type_id='.$row['content_type_id'].'">';
                        $button_0 .= 'edit - '.$get_name['content_type_name'];
                        $button_0 .= '</button>';
                        $button_0 .= "\n".'</form>' ."\n";

                }
        }

        return $rows;//'<pre style="max-width:380px;max-height:100px;overflow-y:scroll;">'.print_r($rows,1).'</pre><span class="btn btn-secondary">'.$number_of_rows.' - fields</span><hr>'. $button_0;
    }

    public function content_type_edit()
    {

        global $cck,$ini_settings, $_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $mdg = 'messages : ';

        $var = array();
        $link = 'link';
        $userID = (isset($_POST['name']) ? $_POST['name']: '');

        $var[$link][1] = array(
                    'text' => 'Profile',
                    'path' => 'users/user_profile/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Account',
                    'path' => 'users/user_settings/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Content',
                    'path' => 'users/user_content/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'Inbox',
                'path' => 'users/user_messages/' .$userID,'css_id' => $this->module,
                'css_class' => array($this->module)
        );

        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        /*$variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);
*/

        $variables['contentTitle'] = $cck->_path_segment(1);

        
            
        /*********************list content types for calendar events**************/

        $db = new SQLite3($database);

        $typeID = (!empty($cck->_path_segment(2)) ? $cck->_path_segment(2) : $_POST['edit_type'] );

        $resultAdd = $db->query('SELECT * FROM content_types WHERE content_type_id ="'.$typeID.'"');

        $count = 1;

        $type_forms = '';

        while ($rowAdd = $resultAdd->fetchArray(SQLITE3_ASSOC)) {
            $rows = array();
            $content_type_list[$rowAdd['content_type_name']] = $rowAdd['content_type_id'];
            $result = $db->query('SELECT * FROM content_type_fields WHERE content_type_id ="'. $rowAdd['content_type_id'].'" ORDER BY weight asc;');
            while ($row = $result->fetchArray(SQLITE3_ASSOC)) {
                $rows[] = $row;

                $form['contentTypeFields'][] = $row; //content type fields are not  content form fields


            }

            $form['contentType'] = $rowAdd['content_type_name'];
            $form['contentTypeId'] = $rowAdd['content_type_id'];
            $form['contentUserId'] = $rowAdd['content_type_user_id'];
            $form['contentTypeCategories'] = $rowAdd['content_type_category_id'];

            $form['formAction'] = '?admin/content_type_field_save/'. $form['contentType'];
            $form['mimeType'] = '';
            $form['header'] = $columns;
            $form['rows'] = $rows;

            $form['contentUserId'] = (isset($form['contentUserId']) ? $form['contentUserId'] : '1');
            $form['userName'] = (isset($form['userName']) ? $form['userName'] : 'owner');
            $form['contentType'] = (isset($form['contentType']) ? $form['contentType'] : '');
            $form['contentId'] = $form['contentType'].'-'.hash('crc32', $cck->_path_segment(1).time() . mt_rand()) .'-'. $form['userName'];

            $form['contentTime'] = date("Y-m-d H:i:s");
            $form['enumerate'] = $count;
            $type_forms .= $cck->_view('form_content_type_edit', $form);
            $count = $count + 1;
        }

        $form_element_types = array(

            'text' => '<input style="" type="text" name="" id="text" style="" class="%s" value="" />',
            'textarea' => '<textarea type="textarea" name="" id="textarea" style="" class="%s"></textarea>',
            'radio' => '<input type="radio" name="" id="radio" style="" class="%s" value="" />',
            'select' => '<select name="" id="select" value="" style="" class="%s"></select>',
            'option' => '<option value="" name="" id="option" style="" class="%s"></option>',
            'datalist' => '<datalist name="" id="datalist" class="%s" value=""></datalist>',
            'checkbox' => '<input type="checkbox" name="" id="checkbox" style="" class="%s" value="" />',
            'date' => '<input type="date" name="" id="date" class="%s" value="" />',
            'date-time' => '<input type="datetime-local" name="" id="datetime-local" class="%s" value="" /> ',
            'email' => '<input type="email" name="" id="email" class="%s" value="" /> ',
            'file' => '<input type="file" name="" id="file" class="%s" value="" /> ',
            'hidden' => '<input type="text" name="" id="hidden" class="%s" value="" />'."\n".'<input type="hidden" name="" id="hidden" class="" value="" />',
            'image' => '<input type="image" name="" id="image" class="%s" value="" /> ',
            'month' => '<input type="month" name="" id="month" class="%s" value="" /> ',
            'week' => '<input type="week" name="" id="week" class="%s" value="" /> ',
            'number' => '<input type="number" name="" id="number" class="%s" value="" /> ',
            'password' => '<input type="password" name="" id="password" class="%s" value="" /> ',
            'range' => '<input type="range" name="" id="range" class="%s" value="" />',
            'reset' => '<button type="reset" value="" name="" id="reset" style="" class="%s" role="button">reset</button>',
            'search' => '<input type="search" name="" id="search" style="" class="%s" value="" /> ',
            'submit' => '<button type="submit" formaction="" value="" name="" id="" style="" class="%s" role="button">submit</button>',
            'time' => '<input type="time" name="" id="" style="" class="%s" value="" />',
            'url' => '<input type="url" name="" id="" style="" class="%s" value="" />',
            'color' => '<input type="color" name="" id="" style="" class="%s" value="" />'
            );
            $list_element_types='';
            $element_css_classes = 'form-control';
            foreach ($form_element_types as $name => $value) {
                switch($name){
                    case 'select':
                        $element_css_classes = 'form-select';
                        break;
                    case 'checkbox':
                        $element_css_classes = 'form-check-input';
                        break;
                    case 'range':
                        $element_css_classes = 'form-range';
                        break;
                    case 'color':
                        $element_css_classes = 'form-control form-control-color';
                        break;

                    default:
                    $element_css_classes = 'form-control';
                }
                $attributes = '<table>'."\n";
                for ($i = 0; $i < $result->numColumns(); $i++) {
                    $col = $result->columnName($i);
                    $attributes  .= '<tr><td style="min-width:120px;">'.$col.'</td><td><input style="" type="text" name="" id="text" style="" class="form-control" value="" /></td></tr>'."\n";
                }

                $attributes .= '</table>'."\n";
                
                $value = sprintf($value,$element_css_classes);
                $list_element_types .=  '<div style="border-bottom: solid 1px #cccccc;">'."\n";
                $list_element_types .= '<h5 style="padding:.5rem 0 .5rem 1rem;border:solid #666666 1px;background-color: #eaeaea;" class="form-label" for="'.$name.'" name="" id="">'.$name.'</h5>'."\n";
              
                $list_element_types .= '<div style="max-height: 400px; overflow-y: scroll; font-size:1rem;font-weight:500;" class="">'."\n";
                $list_element_types .= '<h6 class="sticky">preview</h6>'."\n";
                $list_element_types .= $value . '';
                $list_element_types .= '<a class="target-attr" href="javascript:;" name="'.$form['contentType'] .'_field_'.$name.'_control" id="'.$form['contentType'] .'-field-'.$name.'-control">'."\n";
                $list_element_types .= 'edit attributes: show</a><div id="show-attr" class="show-attr"><pre class="field-attr" id="">'. print_r($attributes,1).'</pre></div>'."\n";
                $list_element_types .= '<div class="text-center"><a role="button" style="background-color:red;color: white;display:none;text-align: center" href="javascipt:;" id="'.$name.'" class="attr-close btn">close</a></div>'."\n";
                $list_element_types .= '</div></div><br>'."\n";
        
        
        
                //break;
            }
        $msg = "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
            
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        $variables['content'] = '<div class="row"><div style="min-width:420px;" class="col">'. $type_forms.'</div><div style="max-width:420px;" class="col"><h5 style="padding:.5rem 0 .5rem 1rem;border:solid #666666 1px;background-color: #eaeaea;">Add fields</h5><div style="max-height:400px;overflow-y:scroll;" name="'.$form['contentType'].'-fields" class="target"><pre>'.print_r($_POST, 1).'</pre>'. $list_element_types.'</div></div>';
        print $cck->_view('page_admin', $variables);
    }

    
    public function content_type_save()
    {

        global $cck,$ini_settings,$_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';



        $userID = $cck->_path_segment(2);
        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Profile',
                    'path' => 'admin/admin_user_profiles/'. $userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Account',
                    'path' => 'admin/admin_user_accounts/',
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Content',
                    'path' => 'admin/admin_user_content/'. $userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'Settings',
                'path' => 'admin/edit_user_settings/'. $userID,
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                'text' => 'Inbox',
                'path' => 'admin/admin_user_messages/'. $userID,
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );


        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'Save content';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);
        foreach ($_POST as $key => $value) {
            $output .= 'key=' . $key . '   :   : value= ' . $value . "<br>\n";
        }
        $output = '<p class="fs-6">' .$output.'</p>'."\n";
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        $variables['POST'] = $_POST;
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);

    }

    public function content_type_post()
    {

        global $cck,$ini_settings,$_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $msg = 'maessages : ';

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['contentTitle'] = 'Create Content';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);

        //$link = 'links';
        $userID = $cck->_path_segment(2);
        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Profile',
                    'path' => 'admin/admin_user_profiles/'. $userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Account',
                    'path' => 'admin/admin_user_accounts/' . $userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Content',
                    'path' => 'admin/admin_user_content/'. $userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'Settings',
                'path' => 'admin/edit_user_settings/'. $userID,
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                'text' => 'Inbox',
                'path' => 'admin/admin_user_messages/'. $userID,
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );

        $form_element_types = array(

            'input' => 'input',
            'textarea' => 'textarea',
            'radio' => 'radio',
            'select' => 'select',
            'checkbox' => 'checkbox',
            'date' => 'date',
            'date-time' => 'datetime-local',
            'email' => 'email',
            'file' => 'file',
            'hidden' => 'hidden',
            'image' => 'image',
            'month' => 'month',
            'week' => 'week',
            'number' => 'number',
            'password' => 'password',
            'range' => 'range',
            'reset' => 'reset',
            'search' => 'search',
            'submit' => 'submit',
            'text' => 'text',
            'time' => 'time',
            'url' => 'url',
            'color' => 'color'
            );

        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Site Admin';
        $variables['adminMenuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Site Admin';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
                'template' => 'links_user_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ), $variables);


        $db = new SQLite3($database);

        $typeID = $cck->_path_segment(2);

        $resultAdd = $db->query('SELECT * FROM content_types WHERE content_type_id ="'. $typeID.'";');
        $result = $db->query('SELECT * FROM content_type_fields WHERE content_type_id ="'. $typeID.'" ORDER BY weight asc;');

        while ($row = $result->fetchArray()) {
            $rows[] = $row;

        }


        while ($rowAdd = $resultAdd->fetchArray()) {
            $table['contentType'] = $rowAdd['content_type_name'];

            $r[] = $rowAdd;
        }
        //var_dump($rows);
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[$col] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $table['fieldType'] = '';
        $table['contentTypeId'] = $typeID;
        $output = $cck->_view('table_content_add_form', $table);


        $table['CCK'] = $cck;
        $table['INI'] = $ini_settings;
        $table['POST'] = $_POST;
        $variables['content'] = 'create new content using <h3><i>'.$table['contentType'].'</i></h3>' . $output;

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']:'');
        $variables['VAR'] = $variables;
        print $cck->_view('page_admin', $variables);

    }

    public function content_type_submit()
    {
        global $cck, $ini_settings;
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['POST'] = $_POST;
        $msg = 'messages : ';
        $variables['messages'] = $msg;

        $variables['content'] = 'create new content using <h3><i>'.$table['contentType'].'</i></h3>' . $output;

        print $cck->_view('page_admin', $variables);
    }
}

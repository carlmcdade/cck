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
        $variables['loggedInUser'] = $_SESSION;
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
        $variables['contentTitle'] = 'admin site modules';
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
        global $cck;
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
        global $cck;
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


        $userID = $cck->_path_segment(2);
        if (!empty($typeID)) {
            $result = $db->query('SELECT id,name,desc FROM content_types WHERE id='.$typeID.'');
        } else {
            $result = $db->query('SELECT id,name,desc FROM content_types');
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
        $output = $cck->_view('table_content_types_admin', $table);

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


        $variables['content'] = 'admin content types' . $output;

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
        $variables['VAR'] = $variables;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        
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
                'path' => 'users/user_messages/' .$userID,
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
        $userID = $cck->_path_segment(2);
        $link = 'links';

        $var = array();

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
        $variables['pageTitle'] = 'admin permissions';
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
        $output =  '<pre>CHECK CREDENTIALS:'. print_r($user_check($_POST['Username'], $_POST['Password']), 1).
        '<hr>POST:'.print_r($_POST, 1).'<hr>SESSION:'.print_r($_SESSION, 1).
        '<hr>USERS:'.print_r($ini_settings['Users'], 1).

        '</pre>';//$cck->_view('forms_admin_login', $variables);
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['content'] =  $output;

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        print $cck->_view('page_user_login', $variables);


    }

    public function logout_user()
    {
        global $cck,$ini_settings,$_SESSION;
        session_destroy();
        exit('logged out');
       
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
        $userID = $_POST['name'];

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
        
            $variables['CCK'] = $cck;
            $variables['INI'] = $ini_settings;
            $variables['formName'] = 'form_login_user';
            $variables['postUrl'] = '?admin/login_check';
            $variables['content'] =  $output;
    
            $msg .= "";
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
        $variables['content'] = '<pre>'.print_r($_POST, 1). print_r($form_element_types, 1).'</pre>';
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
        $variables['contentTitle'] = 'admin content';
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

        $resultAdd = $db->query('SELECT * FROM content_types WHERE type_id ="'. $typeID.'";');
        $result = $db->query('SELECT * FROM content_type_fields WHERE content_type_id ="'. $typeID.'" ORDER BY weight asc;');

        while ($row = $result->fetchArray()) {
            $rows[] = $row;

        }


        while ($rowAdd = $resultAdd->fetchArray()) {
            $table['contentType'] = $rowAdd['name'];

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
        $table['contentType'] = (isset($table['contentType']) ? $table['contentType'] : '');
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
        $variables['content'] = 'create new content using <h3><i>'.$table['contentType'].'</i></h3>' . $output;

        print $cck->_view('page_admin', $variables);
    }
}

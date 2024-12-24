<?php

namespace content;

// classes used by the global $cck object from the globalspace

use Common;
use SQLite3;

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
 *                        content.class.inc
 *
 * ==================================================================
 * This CCK example site is built around this blogging module.
 * It handles the blog content type
 *
 *
 */

class content
{
    public $common;
    public $menu;
    public $section;
    public $module;


    public function __construct()
    {
        // Common settings
        $this->module = __NAMESPACE__;
    }

    public function hook_links($index = null)
    {
        global $cck,$ini_settings;

        $database = $ini_settings['databases']['user_db'];
        $db = new SQLite3($database);




        $result = $db->query('SELECT content_type_id,content_type_name,content_type_description FROM content_types');
        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }

        //var_dump($rows); exit;
        $link = 'links';
        /* foreach ($rows as $key => $value) {
             $var[$link][$key] = array(
                 'text' => $value['name'],
                 'path' => $this->module . '/content_add_post/' . $value['id'],
                 'css_class' => array($this->module, 'module_item'),
                 'css_id' => $this->module . ''
                 );
         }
*/
        $var[$link][] = array(
                'text' => 'Create',
                'path' => $this->module . '/content_create',
                'css_class' => array($this->module, 'main_item'),
                'css_id' => $this->module
                );

        return $var;
    }

    public function hook_module_links($index = null)
    {
        global $cck,$ini_settings;

        $database = $ini_settings['databases']['user_db'];
        $db = new SQLite3($database);




        $result = $db->query('SELECT content_type_id,content_type_name,content_type_description FROM content_types');
        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }

        //var_dump($rows); exit;
        $link = 'links';
        foreach ($rows as $key => $value) {
            $var[$link][$key] = array(
                'text' => $value['content_type_name'],
                'path' => $this->module . '/content_add_post/' . $value['content_type_id'],
                'css_class' => array($this->module, 'module_item'),
                'css_id' => $this->module . ''
                );
        }

        $var[$link][] = array(
                'text' => 'Create Container',
                'path' => $this->module . '/content_container_create',
                'css_class' => array($this->module, 'main_item'),
                'css_id' => $this->module
                );

        return $var;
    }


    public function content_user_list()
    {

        global $cck,$ini_settings;
        $output = 'A list of this users content';

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $variables['seperators'] = array('|','-',';',':');

        $variables['dbTable'] = 'content';

        $variables['pageTitle'] = 'Content';
        $variables['contentTitle'] = 'Content list';
        $variables['menuTitle'] = 'Add content';

        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
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
        $variables['content'] = $output;
        print $cck->_view('default', $variables);
    }

    public function content_types()
    {
        global $cck,$ini_settings;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();

        //some variables to load into the view will appear as $[variable name]
        $output = '';
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $variables['seperators'] = array('|','-',';',':');
        $variables['pageTitle'] = 'Content';
        $variables['menuTitle'] = 'Add Content';
        $variables['adminMenuTitle'] = 'Content Admin';
        $variables['contentTitle'] = 'Content Types';
        $variables['dbTable'] = 'content_types';


        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_class' => array($this->module, 'main_item'),
                'css_id' => $this->module
                ),
            $variables
        );
        

        $link = 'links';

        $var = array();

        
        $var[$link][1] = array(
            'text' => 'Content List',
            'path' => 'content/content_list',
            'css_id' => $this->module,
            'css_class' => array($this->module)

            );
        $var[$link][2] = array(
                    'text' => 'Content Containers (Books)',
                    'path' => 'content/content_containers',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)

                        );
        $var[$link][3] = array(
                    'text' => 'Content Types',
                    'path' => 'content/content_types',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
            
                                );
        $var[$link][5] = array(
                    'text' => 'Content Permissions',
                    'path' => 'content/content_permissions',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $admin_menu = $var;

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
            'template' => 'links_user_menu',
            'index' => $this->module,
            'css_id' => $this->module,
            'css_class' => array($this->module)
            ), $variables);

        $db = new SQLite3($database);


        $typeID = $cck->_path_segment(2);
        if (!empty($typeID)) {
            $result = $db->query('SELECT id,name,desc FROM content_types WHERE content_type_id='.$typeID.'');
        } else {
            $result = $db->query('SELECT * FROM content_types');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
            //$table['contentType'] = $row['content_type_name'];
            //$table['contentTypeId'] = $row['content_type_id'];
            //$table['contentTypeTitle'] = $row['content_type_title'];
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = array('    ', 'type', 'description');
        
        $table['rows'] = $rows;
        $output = $cck->_view('table_content_types', $table);

        foreach ($rows as $key => $value) {
            $variables['userBio'] =  '';
            $variables['userName'] = $value['content_type_name'];
            $variables['profileImage'] = '';
            $variables['userID'] = '';
        }

        $variables['content'] = 'Content types' . $output;

        print $cck->_view('default', $variables);
    }

    public function content_type_edit()
    {
        global $cck,$ini_settings;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();

        //some variables to load into the view will appear as $[variable name]
        $output = '';
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $variables['seperators'] = array('|','-',';',':');
        $variables['pageTitle'] = 'Content';
        $variables['menuTitle'] = 'Content';
        $variables['contentTitle'] = 'Content Types';
        $variables['dbTable'] = 'content_types';


        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_class' => array($this->module, 'main_item'),
                'css_id' => $this->module
                ),
            $variables
        );

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
        $table['header'] = array('action', 'type', 'description');
        $table['rows'] = $rows;
        $output = $cck->_view('table_content_types', $table);

        foreach ($rows as $key => $value) {
            $variables['userBio'] =  '';
            $variables['userName'] = $value['name'];
            $variables['profileImage'] = '';
            $variables['userID'] = '';
        }

        $variables['content'] = 'Content types' . $output;

        print $cck->_view('default', $variables);
    }

    public function content_container_list(){


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
        $variables['contentTitle'] = 'Content Containers';
        $variables['dbTable'] = 'content_containers';

        //$link = 'links';

        $link = 'links';

        $var = array();


        $var[$link][1] = array(
                    'text' => 'Content List',
                    'path' => 'content/content_list',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)

                    );
        $var[$link][2] = array(
                    'text' => 'Content Containers (Books)',
                    'path' => 'content/admin_containers',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
    
                        );
        $var[$link][3] = array(
                    'text' => 'Content Types',
                    'path' => 'content/content_types',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
            
                                );
        $var[$link][4] = array(
                    'text' => 'Content Add',
                    'path' => 'content/content_create',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][5] = array(
                    'text' => 'Content Permissions',
                    'path' => 'content/content_permissions',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $admin_menu = $var;
        //$admin_menu = $cck->_hooks('hook_module_links');

        $db = new SQLite3($database);


        $containerID = $cck->_path_segment(2);
       
            $resultSingle = $db->query('SELECT * FROM content_containers WHERE container_id="'.$containerID.'"');
        
            $result = $db->query('SELECT * FROM content_containers');
        
        while ($row = $result->fetchArray(SQLITE3_ASSOC)) {
            $rows[$row['container_name']] = $row;
        }
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
           // $button_1 .= "\n".'  <input type="hidden" name="'.$row['content_type_name'].'_fields'.'[available_fields][field_attr]['.$col.']" id="Posted-form-posted-fields-field-attr-'.$col.']" value="'.$col.'" />';
            //$button_1 .= '<input type="hidden" name="Posted-form[posted-fields][]"  id=""  value="" />'."\n";
            
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


        $variables['content'] = 'list:<pre>'. print_r($columns,1).'<hr>' .print_r($rows,1).'</pre>';

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        

        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_content', $variables);
        
          



    }

    public function content_container_create(){


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
        $variables['contentTitle'] = 'Content Containers';
        $variables['dbTable'] = 'content_containers';

        //$link = 'links';

        $link = 'links';

        $var = array();


        $var[$link][1] = array(
                    'text' => 'Content List',
                    'path' => 'content/content_list',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)

                    );
        $var[$link][2] = array(
                    'text' => 'Content Containers (Books)',
                    'path' => 'content/admin_containers',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
    
                        );
        $var[$link][3] = array(
                    'text' => 'Content Types',
                    'path' => 'content/content_types',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
            
                                );
        $var[$link][4] = array(
                    'text' => 'Content Add',
                    'path' => 'content/content_create',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][5] = array(
                    'text' => 'Content Permissions',
                    'path' => 'content/content_permissions',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $admin_menu = $var;
        //$admin_menu = $cck->_hooks('hook_module_links');

        $db = new SQLite3($database);


        $containerID = $cck->_path_segment(2);
       
            $resultSingle = $db->query('SELECT * FROM content_containers WHERE container_id="'.$containerID.'"');
        
            $result = $db->query('SELECT * FROM content_containers');
        
        while ($row = $result->fetchArray(SQLITE3_ASSOC)) {
            $rows[$row['container_name']] = $row;
        }
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
           // $button_1 .= "\n".'  <input type="hidden" name="'.$row['content_type_name'].'_fields'.'[available_fields][field_attr]['.$col.']" id="Posted-form-posted-fields-field-attr-'.$col.']" value="'.$col.'" />';
            //$button_1 .= '<input type="hidden" name="Posted-form[posted-fields][]"  id=""  value="" />'."\n";
            
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


        $variables['content'] = 'list:<pre>'. print_r($columns,1).'<hr>' .print_r($rows,1).'</pre>';

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        

        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_content', $variables);
        
          



    }

    public function content_create()
    {
        global $cck,$ini_settings, $_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();

        //some variables to load into the view will appear as $[variable name]
        $output = '';
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $variables['seperators'] = array('|','-',';',':');
        $variables['pageTitle'] = 'Content';
        $variables['menuTitle'] = 'Add Content';
        $variables['adminMenuTitle'] = 'Content Admin';
        $variables['contentTitle'] = 'Content Types';
        $variables['dbTable'] = 'content_types';


        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_class' => array($this->module, 'main_item'),
                'css_id' => $this->module
                ),
            $variables
        );
        

        $link = 'links';

        $var = array();

        
        $var[$link][1] = array(
            'text' => 'Content List',
            'path' => 'content/content_list',
            'css_id' => $this->module,
            'css_class' => array($this->module)

            );
        $var[$link][2] = array(
                    'text' => 'Content Containers (Books)',
                    'path' => 'content/content_containers',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)

                        );
        $var[$link][3] = array(
                    'text' => 'Content Types',
                    'path' => 'content/content_types',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
            
                                );
        $var[$link][5] = array(
                    'text' => 'Content Permissions',
                    'path' => 'content/content_permissions',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $admin_menu = $var;

        $variables['adminNavigation'] = $cck->_module_links($admin_menu, array(
            'template' => 'links_user_menu',
            'index' => $this->module,
            'css_id' => $this->module,
            'css_class' => array($this->module)
            ), $variables);

        $db = new SQLite3($database);


        $typeID = $cck->_path_segment(2);
        if (!empty($typeID)) {
            $result = $db->query('SELECT * FROM content_types WHERE content_type_id='.$typeID.'');
        } else {
            $result = $db->query('SELECT * FROM content_types');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
            //$table['contentType'] = $row['content_type_name'];
            //$table['contentTypeId'] = $row['content_type_id'];
            //$table['contentTypeTitle'] = $row['content_type_title'];
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = array('  ', 'type', 'description');
        
        $table['rows'] = $rows;
        $output = $cck->_view('table_content_types', $table);

        foreach ($rows as $key => $value) {
            $variables['userBio'] =  '';
            $variables['userName'] = $value['content_type_name'];
            $variables['profileImage'] = '';
            $variables['userID'] = '';
        }

        $variables['content'] = 'Content types' . $output;

        print $cck->_view('default', $variables);
    }

    public function content_post_save()
    {
        global $cck,$ini_settings,$_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();


        $menu = $cck->_hooks('hook_links');
        $variables['page_title'] = 'Saved';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $db = new SQLite3($database);
        if (!empty($typeID)) {
            $result = $db->query('SELECT * FROM content WHERE id='. $view_id .'');
        } else {
            $result = $db->query('SELECT * FROM content');
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
        //$output .= $cck->_view('table_content_add', $table);

        $view_content['content_body'] = $_POST;
        //$view_content['content_json'] = json_encode($_POST, JSON_PRETTY_PRINT);
        $view_content['content_type'] = $_POST['content_type'];
        $view_content['content_id'] = $_POST['content_id'];
        $view_content['content_time_created'] = $_POST['content_time'];
        $view_content['content_published'] = false;
        $view_content['content_type_id'] = $_POST['content_type_id'];
        $view_content['content_category_id'] = $_POST['content_type_categories'];
        $view_content['content_user_id'] = $_POST['content_user_id'];
        $view_content['content_form_fields'] = array_keys($_POST);


        $view_id = $cck->_path_segment(2);


        $output = $this->module;
        $output .= '<pre>';
        $output .= print_r($view_content,1);
        $output .= '</pre>';



        $variables['pageTitle'] = $view_id .' Saved';
        $variables['contentTitle'] = $view_id .' Saved';
        $variables['content'] =  $output;
        print $cck->_view('page_users_content', $variables);

    }

    public function content_add_post(){


        global $cck,$ini_settings, $_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $variables['seperators'] = array('|','-',';',':');
        $variables['pageTitle'] = 'Content Create';
        $variables['menuTitle'] = 'Create';
        $variables['adminMenuTitle'] = 'Content Admin';
        $variables['contentTitle'] = 'Content';
        $variables['dbTable'] = 'content';
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        
        $link = 'links';

        $var = array();

        
        $var[$link][1] = array(
            'text' => 'Content List',
            'path' => 'content/content_list',
            'css_id' => $this->module,
            'css_class' => array($this->module)

                    );
        $var[$link][2] = array(
                    'text' => 'Content Containers (Books)',
                    'path' => 'content/container_list',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)

                        );
        $var[$link][3] = array(
                    'text' => 'Content Types',
                    'path' => 'content/content_types',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
            
                                );
        
        $var[$link][4] = array(
                    'text' => 'Content Permissions',
                    'path' => 'content/content_permissions',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $admin_menu = $var;
        

        $db = new SQLite3($database);
        $count = 1;
        $button_0 = '';
        $type_forms = '';
        $listID = (!empty($cck->_path_segment(2)) ? $cck->_path_segment(2) : '1');

            $result = $db->query('SELECT * FROM content WHERE content_type_id ="'. $listID.'" ORDER BY content_name asc;');

            $number_of_rows = 0;//for now

            while($row = $result->fetchArray()) {
                $number_of_rows += 1;
            }
        

                
            
                        
                        $result = $db->query('SELECT * FROM content WHERE content_type_id ="1"');
                        $resultType = $db->query('SELECT * FROM content_types WHERE content_type_id="'.$listID.'"');
                        while ($cType = $resultType->fetchArray()) {
                            $type_info = $cType;
                        }
                        //var_dump($get_name);
                        $button_0 = "\n".'<div class="col">';
                        $button_0 .= "\n".'<div class="bg-black border p-1 text-center fs-2 text-white">'. $type_info['content_type_name'] . '</div>';
                        //$button_0 .= '<div style="color:white;text-align:center;margin:12px 12px 12px 0px;" class="col bg-black border">'.$row['content_name'].'| -> |'.$row['content_machine_id'].'|</div>';
                                   
                        $button_0 .= "\n\n\t\t".'<div class="row"> <div class="col border border-black border-end-0"><div class="bg-primary text-center border border-black border-top-0">content fields</div><form style="border:0px;" name="save_content" id="form-save-content" class="" method="post">'."\n";
                        $resultFields = $db->query('SELECT * FROM content_type_fields WHERE content_type_id="'.$listID.'"');
                                    while ($tField = $resultFields->fetchArray(SQLITE3_ASSOC)) {

                                        $field_typed = $tField['field_type'];
                                        $contentTypeFields[]= $tField;
                                        $p_rows[] = $tField;
    
                                        $button_0 .= "\n".'<div style=" width:400px; margin: 0.5rem 0 0.5rem 0">';
                                        $button_0 .= "\n".'<div class="btn-primary border p-1">'.$tField['label'].'</div>';
                                        $button_0 .=  "\n".'<div class="border bg-dark text-end p-1">';


                                        if($tField['field_type'] == 'select'){

                                        
                                        $resultFieldsOptions = $db->query('SELECT * FROM content_type_field_options WHERE content_type_field_id="'.$tField['machine_id'].'"');
                                        $option_list = '';
                                    

                                        $option_list .= "\n" .$tField['title'].'<select class="'.$tField['css_sheet'].'" style="'.$tField['css_inline'].'" type="'.$tField['field_type'].'" name="content_body['.$tField['name'].':'.$tField['label'].']" value="" >';
                                        
                                                while ($fOption = $resultFieldsOptions->fetchArray(SQLITE3_ASSOC))
                                                {

                                                    $option_list .= "\n".'<option value="'. $fOption['option_value'] .'" name="name-'.$fOption['option_html_name'].'-'.$fOption['option_machine_id'].'" id="id-'.$fOption['option_html_id'].'-'.$fOption['option_machine_id'].'">'. $fOption['option_label'] . '</option>';

                                                }

                                        $option_list .= "\n".'</select>';
                                        $button_0 .= $option_list;
                                        $button_0 .= "\n".'<a class="btn btn-secondary p-1" role="button" name="content_body['.$tField['name'].':'.$tField['label'].']" value="test '.$tField['name'].
                                            '" href="?admin/edit_type_field/'.$tField['machine_id'].'">edit</a>';
                                            $button_0 .= "\n".'<details class="detail-box" style="padding:3px;margin-top:5px;text-align:left; background-color:#fefefe'.$tField['css_inline'].'"><summary>description</summary><p>'.$tField['description'].'</p></details>';
                                        

                                        }else{

                                            $button_0 .= "\n".'<input type="text" name="content_body['.$tField['name'].':'.$tField['label'].']" value="test '.$tField['name'].'" />';
                                            $button_0 .= "\n".'<a class="btn btn-secondary p-1" role="button" name="content_body['.$tField['name'].':'.$tField['label'].']" value="test '.$tField['name'].
                                            '" href="?admin/edit_type_field/'.$tField['machine_id'].'">edit</a>';
                                            $button_0 .= "\n".'<details class="detail-box" style="padding:3px;margin-top:5px;text-align:left; background-color:#fefefe'.$tField['css_inline'].'"><summary>description</summary><p>'.$tField['description'].'</p></details>';
                                        
                                        }
                                        $button_0 .= "\n".'</div>';
                                        $button_0 .= "\n".'</div>';

                                        /* if list then */
                                                
                                            
                                        
                                        

                                           
                                    }
                                    $button_0 .= "\n".' <button role="button" class="btn btn-secondary" type="submit" formaction="?admin/content_save&content_id='. 
                                    $listID.'">save content body</button>';
                                    $button_0 .= "\n".'</div><div class="col border border-black"><div class="bg-primary text-center border border-black border-top-0">container fields</div>';
                                    
                            
                        for ($i = 0; $i < $result->numColumns(); $i++) 
                        {
                                $col = $result->columnName($i);
                                $columns[] = $col;
                                $field_value = '';
                                $field_disable = '';
                                $field_typed = 'text';
                                $field_labeled = "\n".'<div class="col-3">'.$col.'</div>';
                                $field_style= '';

                                switch($col){

                                    case 'id':
                                        $field_typed =  'hidden';
                                        $field_labeled = '';
                                    break;
                                    case 'content_user_id':
                                        $field_value = 'guest';
                                        $field_disable = 'READONLY';
                                        $field_style = 'border:solid 1px black;background-color: #eaeaea;';
                                    break;
                                    case 'content_id':
                                    case 'content_machine_id':
                                        $field_value =  $type_info['content_type_name'].'-'.hash('crc32', $cck->_path_segment(1).time() . mt_rand()) .'-user';
                                        $field_disable = 'READONLY';
                                        $field_style = 'border:solid 1px black;background-color: #eaeaea;';
                                    break;
                                    case 'content_container_id':
                                        $field_value =  'container-'.hash('crc32', $type_info['content_type_name'].time() . mt_rand()) .'-'.$type_info['content_type_name'];
                                        $field_disable = 'READONLY';
                                        $field_style = 'border:solid 1px black;background-color: #eaeaea;';
                                    break;
                                }

                                
                                
                               
                                 
                                if($col == 'content_body'){
                                   
                                   
                                    
                                } else {

                                   
                                        
                                            $button_0 .= '';
                                            $button_0 .= "\n" .$field_labeled.'<input style="'.$field_style.'" type="'.$field_typed.'" name="'.$col.'" value="'.$field_value.'" '.$field_disable.' />';
                                   

                                    
                                }
                                    
                                

                }
                            $button_0 .= "\n".'' ."\n";
                            
                        


              /*  while ($row = $result->fetchArray(SQLITE3_ASSOC)) {
                        $rows[$row['content_machine_id'].'-'. $row['content_name'].'-'. $row['content_machine_id']] = $row;
                        $get_name = $db->querySingle('SELECT * FROM content WHERE content_type_id='.$row['content_type_id'], true);
                        //var_dump($get_name);
                        $button_0 .= '<div class="col" style="margin-bottom:1rem;border-bottom:2px solid black;padding-bottom:1rem;">';
                        $button_0 .= '<div style="color:white;text-align:center;margin:12px 12px 12px 0px;" class="col bg-black border">'.$row['content_name'].'| -> |'.$row['content_machine_id'].'|</div>';
                                   
                        //$button_0 .= "\n\n\t\t".'<form style="border:0px;" name="save_'.$row['content_name'].'" id="form-field-id-'.$row['content_machine_id'].'" class="" method="post">'."\n";
                        
                            for ($i = 0; $i < $result->numColumns(); $i++) {
                                $col = $result->columnName($i);
                                $columns[] = $col;
                                $button_0 .= "\n" . '<div class="row"><div class="col">'.$col.'</div><div class="col">  <input type="text" name="'.$col.'" value="'.$row[$col].'" /></div></div>';
                                
                                if($col == 'content_body'){
                                    $button_0 .= '<div class="row">';
                                    $button_0 .= '<div style="text-align:center;margin:12px 12px 12px 0px;" class="col bg-secondary border"> Content body [type fields]</div></div>';
                                    //$button_0 .= '<form name="save_'.$row['content_name'].'" id="" method="post">';
                                    $resultFields = $db->query('SELECT * FROM content_type_fields WHERE content_type_id="'.$row['content_type_id'].'"');
                                    while ($tField = $resultFields->fetchArray(SQLITE3_ASSOC)) {
                                        $contentTypeFields[]= $tField;
                                        $p_rows[] = $tField;
    
                                        $button_0 .= "\n".'<div class="row"> <div style="text-align:right;border-bottom: solid #777777 2px;padding: 2px 2px 2px 12px; margin-bottom: 0.75rem;" class="bg-primary border col">';
                                        $button_0 .=  ''.$tField['name'].'</div>';
                                        $button_0 .=  '<div class="col"><input type="text" name="content_body['.$tField['name'].']" value="test '.$tField['name'].'" /></div></div>';
                               
                                           
                                    }
                                    $button_0 .= '<div style="padding:5px 3px;text-align:center;margin:12px 12px 12px 0px;" class="col bg-secondary border"> <button role="button" class="btn btn-secondary" type="submit" formaction="?admin/content_save&content_id='. 
                                    $row['content_machine_id'].'">save content body</button></div>';
                                    $button_0 .= '';
                                    //$button_0 .= '</div>';
                                    $col_value = 'show the fields for this type by id';
                                } else {
    
                                    $col_value = 'end of row</form>';
                                }
                                
                            }
                            
                        
                        
                        $button_0 .= '<span>'.$col_value.'</span>';
                        $button_0 .= '';
    
                        $button_0 .= "\n".'<label>'.$row['content_machine_id'].'</label>   <input type="text" name="Posted_'.$row['content_name'].'[content_field]['.$row['content_machine_id'].'][machine_id]" id="Posted-form-posted-content-type-field-options-list" value="'.$row['content_machine_id'].'" /><br>';
                        $button_0 .= "\n".'<label>'.$row['content_title'].'</label>  <input type="text" name="Posted_'.$row['content_name'].'[content_field]['.$row['content_machine_id'].'][title]" id="Posted-form-posted-content-type-field-html-tag" value="'.$row['content_title'].'" /><br>';
                        $button_0 .= "\n".'<label>'.$row['content_time_created'].'</label>   <input type="text" name="Posted_'.$row['content_name'].'[content_field]['.$row['content_machine_id'].'][created]" id="Posted-form-posted-content-type-field-options-html-role" value="'.$row['content_time_created'].'" /><br>';
                        $button_0 .= "\n".'<label>'.$row['content_user_id'].'</label>   <input type="text" name="Posted_'.$row['content_name'].'[content_field]['.$row['content_machine_id'].'][user]" id="Posted-form-posted-content-type-field-placeholder" value="'.$row['content_user_id'].'" /><br>';
                        $button_0 .= "\n".'<label>'.$row['content_category_id'].'</label>   <input type="text" name="Posted_'.$row['content_name'].'[content_field]['.$row['content_machine_id'].'][category]" id="Posted-form-posted-content-type-field-description" value="'.$row['content_category_id'].'" /><br>';
                        $button_0 .= "\n".'<label>'.$row['content_published'].'</label>   <input type="text" name="Posted_'.$row['content_name'].'[content_field]['.$row['content_machine_id'].'][published]" id="Posted-form-posted-content-type-field-label" value="'.$row['content_published'].'" /><br>';
                        $button_0 .= "\n".'<label>'.$row['content_js'].'</label>  <input type="text" name="Posted_'.$row['content_name'].'[content_field]['.$row['content_machine_id'].'][js]" id="Posted-form-posted-content-type-field-value" value="'.$row['content_js'].'" /><br>';
                       
                       
                        $button_0 .= "\n".'<label>'.$row['content_id'].'</label>  <input type="text" name="Posted_'.$get_name['content_name'].'[content_field]['.$row['content_machine_id'].'][content_id]" id="Posted-form-posted-content-type-field-options-list" value="'.$row['content_id'].'" /><br>';
                        $button_0 .= "\n".'<label>'.$row['content_type_id'].'</label>  <input type="text" name="Posted_'.$get_name['content_name'].'[content_field]['.$row['content_machine_id'].'][content_type_id]" id="Posted-form-posted-content-type-field-type" value="'.$row['content_type_id'].'" /><br>';
                        $button_0 .= "\n".'<label>'.$row['content_name'].'</label>  <input type="text" name="Posted_'.$get_name['content_name'].'[content_field]['.$row['content_machine_id'].'][content_name]" id="Posted-form-posted-content-type-field-name'.
                        $row['content_type_id'].'" value="'.$get_name['content_name'].'" /><br>';
                        $button_0 .= "\n".'<label>'.$row['content_js'].'</label>  <input type="text" name="Posted_'.$get_name['content_name'].'[content_field]['.$row['content_machine_id'].'][content_id]" id="Posted-form-posted-content-id-'.$row['content_id'].'" value="'.$row['content_id'].'" /><br>';
                        $button_0 .= '<button title="" type="submit" name="create_new_' . $row['content_name'] . '" id="post-button-id-'. $row['content_id'].'" role="button"  class="btn btn-primary" formaction="?admin/content_edit/'. $row['content_id'] .
                        '&content_name='.$row['content_name'].'&content_id='.$row['content_machine_id'].'">';
                        $button_0 .= 'edit - '.$row['content_machine_id'];
                        $button_0 .= '</button>';
                        $button_0 .= "\n".'</form></div>' ."\n";
                        $button_0 .= '</div></div>';

                }*/
        
        $button_0 .= '</div>';
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

        

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;     
       
        $variables['content']  = $button_0;//'<pre>'.print_r($rows,1).'</pre>';//'<pre style="max-width:380px;max-height:100px;overflow-y:scroll;">'.print_r($rows,1).'</pre><span class="btn btn-secondary">'.$number_of_rows.' - fields</span><hr>'. $button_0;
        print $cck->_view('page_users_content', $variables);
    
    

    }

    public function content_add_post_old()
    {

        global $cck,$ini_settings;

        $database = $ini_settings['databases']['user_db'];
        $form = array();
        $columns = array();
        $rows = array();

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Create';
        $variables['pageTitle'] = 'Add Content';
        $variables['contentTitle'] = 'admin content';
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

        $resultAdd = $db->query('SELECT * FROM content_types WHERE content_type_id ="'. $typeID.'";');
        $result = $db->query('SELECT * FROM content_type_fields WHERE content_type_id ="'. $typeID.'" ORDER BY weight asc;');

        while ($row = $result->fetchArray(SQLITE3_ASSOC)) {
            $rows[]= $row;

        }

        $count = 1;
        while ($rowAdd = $resultAdd->fetchArray(SQLITE3_ASSOC)) {
            $form['contentType'] = $rowAdd['content_type_name'];
            $form['contentTypeId'] = $rowAdd['content_type_id'];
            $form['contentUserId'] = $rowAdd['content_type_user_id'];
            $form['contentTypeCategories']['category-'. $count] = $rowAdd['content_type_category_id'];

            $r[] = $rowAdd;
            $count = $count+1;
        }
        //var_dump($rows);
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[$col] = $col;
        }
        $form['formAction'] = '?content/content_post_save/'. $form['contentType'];
        $form['mimeType'] = '';
        $form['header'] = $columns;
        $form['rows'] = $rows;

        $form['contentUserId'] = (isset($form['contentUserId']) ? $form['contentUserId'] : '1');
        $form['userName'] = (isset($form['userName']) ? $form['userName'] : 'owner');
        $form['contentType'] = (isset($form['contentType']) ? $form['contentType'] : '');
        $form['contentId'] = $form['contentType'].'-'.hash('crc32', $cck->_path_segment(1).time() . mt_rand()) .'-'. $form['userName'];
        $form['contentTypeFields']['content_type_fields'] = print_r($rows,TRUE); //content type fields are not  content form fields

        $form['contentTime'] = date("Y-m-d H:i:s");
        $output = $cck->_view('form_user_content_post', $form);



        $variables['content'] = 'create new content using - <h3><i>'.$form['contentType'].'</i></h3>' . $output;

        print $cck->_view('page_form', $variables);

    }

    public function content_add_field()
    {

        global $cck,$ini_settings;

        $database = $ini_settings['databases']['user_db'];
        $form = array();
        $columns = array();
        $rows = array();

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Create';
        $variables['pageTitle'] = 'Add Field to - <i>'. $_POST['content_type'].'</i>';
        $variables['contentTitle'] = 'content type fields';
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



        $variables['content'] = 'create new content using <h3><i>'.$form['contentType'].'</i></h3>' . $output;

        print $cck->_view('page_form', $variables);

    }

    public function content_crud()
    {

        $variables = array();
        $view = 'default';
        $mode = ber_pathpart(2);
        print $mode;

        switch ($mode) {
            // models return a view/model
            case 'create':
                $variables['page_title'] = 'Create One';
                $variables['content'] = $this->common->ber_model('example', 'get_create');
                $view = 'movico';
                break;

            case 'view':

                $variables['page_title'] = 'View One';
                $variables['content'] = $this->common->ber_model('example', 'get_retrieve');
                $view = 'movico';
                break;

            case 'update':

                $variables['page_title'] = 'Update One';
                $output = 'This is a plain string to show the use of the out parameter';

                // doing it a bit different and setting the form into a variable
                $variables['start'] = '<div style="border:1px solid #eaeaea">start</div>'.
                //mvc_access(__function__);
                $variables['myform'] = $this->common->ber_model('example', 'get_update');
                $variables['end'] = '<div style="border:1px solid #eaeaea">end</div>';
                $view = 'movico';
                break;

            case 'delete':
                $variables['page_title'] = 'Delete One';
                $this->common->ber_model('example', 'get_delete');
                $view = 'movico';
                break;
        }
        print $this->common->ber_view($view, $variables);
    }

    public function view()
    {
        global $cck, $ini_settings;
        $view_content = $_SERVER['POST'];
        $view_id = $cck->_path_segment(2);
        $menu = $cck->_hooks('hook_links');
        $variables['page_title'] = 'View One';
        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');

        $output = $this->module;
        $output .= print_r($view_content, true);
        $output .= print_r($view_id, true);


        $variables['content_title'] = $id_content;
        $variables['content'] .=  $output;
        print $cck->_view('default', $variables);
    }

    public function edit()
    {
        global $cck, $ini_settings;
        $menu = $cck->_hooks('hook_links');
        $variables['page_title'] = 'View One';
        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');

        $output = '';

        print_r($this->_form_field('select', 'string'));

        $connect = $cck->_dbconnect();
        $id = $connect->prepare("SELECT * FROM content_type ");
        $id->bindValue(':id', ber_pathpart(2));
        $id->execute();
        $id_result = $id->fetch(PDO::FETCH_ASSOC);
        $id_content = $id_result['ccid'];

        if (!empty($id_content)) {
            // get content type info
            $content_type = $connect->prepare("SELECT * FROM " . $id_result['table']);
            $content_type->execute();
            $content_type_table = $content_type->fetchAll(PDO::FETCH_COLUMN);

            for ($i = 0; $i < $content_type->columnCount(); $i++) {
                $col = $content_type->getColumnMeta($i);
                $columns[] = $col['name'];
            }

            $field_order = $columns;
            unset($field_order[0]);
            $field_order = array_values($field_order);
            $field_order = array_flip($field_order);



            $content = $connect->prepare("SELECT cd.data, cc.* FROM content_collection cc JOIN content_data cd ON cc.data_id = cd.data_id WHERE cc.ccid=:ccid");
            $content->bindValue(':ccid', $id_content);
            $content->execute();
            $content_data = $content->fetchAll(PDO::FETCH_ASSOC);

            foreach ($content_data as $result) {
                $data[] = array_merge($result, $id_result);
            }

            $output .= $id_content . '= view content: <pre>' .  print_r($data, 1);

            foreach ($field_order as $f => $index) {
                $with_data[$f] = $data[$index];
            }

            $user_field_order = array('f1' => 1, 'f2' => 0);
            unset($with_data);
            foreach ($user_field_order as $uf => $uindex) {
                if (isset($data[$uindex])) {
                    $with_data[$uf] = $data[$uindex];
                }
            }

            foreach ($columns as $key => $field) {

                $fields = $connect->prepare("SELECT $field FROM " . $id_result['table']);
                $fields->execute();
                $field_complete = $fields->fetchAll(PDO::FETCH_ASSOC);

                if ($field == 'meta') {
                    foreach ($field_complete as $value) {
                        //
                        $meta[] = $value[$field];
                    }
                } else {
                    //
                    foreach ($field_complete as $value) {
                        //
                        $elements[$field][] = $value[$field];
                    }

                }

            }

            foreach ($elements as $name => $element) {

                foreach ($element as $key => $value) {
                    //
                    $items[$name][$meta[$key]] = $value;
                }
                $items[$name]['field'] = $with_data[$name];
            }


            $output .= print_r($field_order, 1);
            $output .= print_r($with_data, 1);

            $output .= print_r($items, 1);

        } else {
            $output = 'Query incomplete or nothing found!';
        }

        $variables['content_title'] = $id_content;
        $variables['content'] =  $output. '</pre>';
        print $cck->_view('default', $variables);
    }


}

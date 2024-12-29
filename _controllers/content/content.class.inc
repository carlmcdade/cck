<?php

namespace content;

// classes used by the global $cck object from the globalspace

use Common;
use SQLite3;
use PDO;

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
            'text' => 'Create Category',
            'path' => $this->module . '/content_category_create',
            'css_class' => array($this->module, 'main_item'),
            'css_id' => $this->module
            );


        $var[$link][] = array(
                'text' => 'Create Container',
                'path' => $this->module . '/content_container_create',
                'css_class' => array($this->module, 'main_item'),
                'css_id' => $this->module
                );

        return $var;
    }

    public function content_list()
    {
      
            global $cck, $ini_settings,$_SESSION;
    
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
            $variables['iniSettings'] = $ini_settings;
            $variables['menuTitle'] = 'View blog';
            $variables['pageTitle'] = 'Recent posts';
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
            /*========================= bloggers ======================================*/
            $db = new SQLite3($database);
    
            $result = $db->query('SELECT * FROM userlist');
    
            while ($u_row = $result->fetchArray()) {
                $u_rows[] = $u_row;
            }
            //SQLite3Result::numColumns();
            for ($i = 0; $i < $result->numColumns(); $i++) {
                $col = $result->columnName($i);
                $columns[] = $col;
            }
            $table['header'] = $columns;
            $table['rows'] = $u_rows;
            $variables['sideBar'] = $cck->_view('table_blog_latest_sidebar', $table);
            //$variables['userID'] = $cck->_path_segment(2);
            
    
            /* ========================== blog posts ========================== */
    
            $db = new SQLite3($database);
            $table_posts = array();
            $userID = $cck->_path_segment(2);
            
            $resultContent = $db->query('SELECT * FROM content');
            $row_count = 0;
            $content_rows = array();
            while ($row = $resultContent->fetchArray(SQLITE3_ASSOC)) {
                   $row['content_body'] = unserialize($row['content_body']);
                    //$content_rows[$row['content_machine_id']] = $row;
                    $col = $resultContent->columnName($row_count);
                    $resultFieldAttr = $db->query('SELECT * FROM content_field_attributes WHERE field_container_id="'.$col.'" ');
                    $variables['row'] = $row;
                    $output .= $cck->_view('content_type_admin',$variables);
    
                
    
                $row_count = $row_count + 1;
               
            }
    
            //SQLite3Result::numColumns();
            for ($i = 0; $i < $resultContent->numColumns(); $i++) {
                $col = $resultContent->columnName($i);
                $columns[] = $col;
            }
            
    
            $variables['CCK'] = $cck;
            $variables['INI'] = $ini_settings;
            $variables['formName'] = 'form_login_user';
            $variables['postUrl'] = '?admin/login_check';
            

            $msg .= "";
            $variables['messages'] = $msg;
            $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
            $variables['VAR'] = $variables;     
       
            $variables['content_rows'] = $content_rows;
    
            $variables['content'] = $output;//<pre>'. print_r($content_rows,1) .'</pre>';
    
            print $cck->_view('default', $variables);

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
        $variables['contentTitle'] = 'Content Create';
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

        $variables['content'] = 'Choose a content type' . $output;

        print $cck->_view('default', $variables);
    }

    public function content_read()
    {
        
    }

    public function content_edit()
    {
        
        global $cck,$ini_settings, $_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';

        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $variables['seperators'] = array('|','-',';',':');
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        

        $db = new SQLite3($database);
        $conID = (isset($_GET['content_machine_id']) ? $_GET['content_machine_id'] : $_GET['content_machine_id']);

        $resultContent = $db->query('SELECT * FROM content WHERE content_machine_id="'.$conID.'"');
        while($rowContent = $resultContent->fetchArray(SQLITE3_ASSOC))
        {
            
            
            $rowContent['content_body'] = unserialize($rowContent['content_body']);

            $content_rows['content_machine_id'] = $rowContent;


        }
        $content_rows['content_database_value'] = serialize($content_rows['content_machine_id']['content_body']);
       
        unset($content_rows['content_machine_id']['content_body']['content_machine_id']);
        unset($content_rows['content_machine_id']['content_body']['database_value']);
        //$output .= '<pre>'. print_r($content_rows,1). '</pre>';
        //$output .= '<pre>'. print_r($_POST,1). '</pre>';
        //echo '<pre>'. print_r($_GET,1). '</pre>';
        echo '<form name="" id="" method="post">';
        if(is_array($content_rows['content_machine_id']['content_body'])){
            foreach($_POST['content_body'] as $f_name => $f_value)
            {
                switch($f_name)
                {

                    case 'database_value':
                        //echo "\n" . '<textarea name="content_body['.$f_name.']" id="'.$f_name.'">'. $f_value .'</textarea>'."\n";
                    break;
                    case 'body':
                        $output .=  "\n" . '<br><label style="display: block;width:300px; color:#ffffff;background-color: #000000; border: solid #000000 1px;">'.$f_name.'</label>
                        <textarea placeholder="main content of post" style="width:300px; height:300px;" name="content_body['.$f_name.']" id="'.$f_name.'"></textarea>'."\n<br>";
                    break;
                    default:
                    $output .=  "\n".'<br><label style="display: block; width: 300px;color:#ffffff;background-color: #000000; border: solid #000000 1px;">'.$f_name.'</label>
                    <input style="width:300px;" class="" type="text" name="content_body['.$f_name.']" id="" value="'.$f_name.'" />'. "<br>";
                    break;
                }

                
                
            }
        }
        else{

            foreach($_POST['content_body'] as $f_name => $f_value)
            {
                switch($f_name)
                {

                    case 'body':
                        $output .=  "\n" . '<br><label style="display: block;width:300px; color:#ffffff;background-color: #000000; border: solid #000000 1px;">'.$f_name.'</label>
                        <textarea placeholder="main content of post" style="width:300px; height:300px;" name="content_body['.$f_name.']" id="'.$f_name.'"></textarea>'."\n<br>";
                    break;
                    default:
                    $output .=  "\n".'<br><label style="display: block; width: 300px;color:#ffffff;background-color: #000000; border: solid #000000 1px;">'.$f_name.'</label>
                    <input style="width:300px;" class="" type="text" name="content_body['.$f_name.']" id="" value="'.$f_name.'" />'. "<br>";
                    break;

                }

                
                
            }


        }
        //echo "\n".'<textarea style="" class="" type="text" name="database_value" id="">'.serialize($content_rows).'</textarea>'. "<br>";
        $output .=  "\n".'<input style="" class="" type="hidden" name="content_machine_id" id="" value="'.$_GET['content_machine_id'].'" />'. "<br>";
        $output .=  "\n".'<button style="" class="btn" type="submit" formaction="?content/content_update&content_machine_id='.$_GET['content_machine_id'].'">save</button>';
        $output .= '</form>';
        $variables['pageTitle'] = 'Content';
        $variables['contentTitle'] = 'Content Update';
        
        $variables['content'] = $output;
        print $cck->_view('page_blog_view', $variables);


    }

    public function content_update()
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

        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        //var_dump($_POST);exit;
        foreach($_POST as $key => $value){

                switch($key){

                    case 'content_body':

                        //$_POST['database_value'] = serialize($_POST['content_body']);

                    break;
                }

        }
        $result = $db->query('SELECT * FROM content');
        

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            if($result->columnName($i) == 'id'){
                continue;
            }
            $col = $result->columnName($i);
            $columns[$col] = $col;
            $column_values[] = ':'.$col;
        }
        //exit('<pre>'.print_r($columns,1).'</pre>');

        try 
        { 
            $pdo = new PDO("sqlite:". $database); // [name].db just creates a new file
   
        } 
    
        catch (PDOException $e)
        {
            echo 'connection failed: '.$e->getMessage();
        }
    
          

        $sql = 'INSERT INTO content('.implode(',',$columns).') VALUES('.implode(',',$column_values).');';

        $stmt = $pdo->prepare($sql);
        
        
        //$updateStmt = $pdo->prepare($sqlUpdate);
        $Upstmt = 'content_body = :body';

        
        
        

        $sqlUpdate = 'UPDATE content SET '.$Upstmt.' WHERE content_machine_id = "'. $_GET['content_machine_id']. '";';
        $stat = $pdo->prepare($sqlUpdate);
        $stat->bindValue(':body', serialize($_POST['content_body']), SQLITE3_TEXT);
        
        $sqlCheck = 'SELECT content WHERE content_machine_id="'.$_GET['content_machine_id'].'";';

        /** execute sql for new post to database **/
        try{
            
            $stat->execute();

        } 
        catch (PDOException $e)
        {
            echo 'update failed: '.$e->getMessage();
        }
        //$stmt->execute();
        
        $output = $this->module;
        $output .= '<pre>';
        $output .= '<hr>'. print_r($sqlUpdate,1) . '<hr>'. print_r($sqlCheck,1);
       
        $output .= '</pre>';

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']: '' );
        $variables['VAR'] = $variables;
        $variables['content'] = $output. '<pre>'.print_r($_POST, 1).'</pre>'.'<pre>'.print_r($_GET, 1).'</pre>'.'</div></div>';
        

        print $cck->_view('page_admin', $variables);


    }

    public function content_delete()
    {

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
                                   
                        $button_0 .= "\n\n\t\t".'<div class="row"> <div class="col border border-black border-end-0"><div class="bg-primary text-center border border-black border-top-0">content fields</div><form style="border:solid1px;" name="save_content" id="form-save-content" class="" method="post">'."\n";
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
                                    

                                        $option_list .= "\n" .$tField['title'].'<select class="'.$tField['css_sheet'].'" style="'.$tField['css_inline'].'" type="'.$tField['field_type'].'" name="content_body['.$tField['name'].':'.$tField['label'].':'.$tField['machine_id'].']" value="" >';
                                        
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

                                            switch($tField['name']){

                                                case '':
                                                    $tField['content_name'] = '';
                                                break;



                                            }

                                            $button_0 .= "\n".'<input type="text" name="content_body['.$tField['name'].':'.$tField['label'].':'.$tField['machine_id'].']" value="'.$tField['name'].'" />';
                                            /**/
                                            $button_0 .= "\n".'<a class="btn btn-secondary p-1" role="button" name="content_body['.$tField['name'].':'.$tField['label'].':'.$tField['machine_id'].']" value="'.$tField['name'].
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
                                $field_style_sheet = '';
                                $option_list = '';
                                $details = '';
                                $details_message = '';

                                $contentFieldsInfo = $db->query('SELECT * FROM content_field_attributes');
                                        while ($conField = $contentFieldsInfo->fetchArray(SQLITE3_ASSOC)) 
                                        {
                                             $content_field_info[$conField['field_container_id']] = $conField ;
                                        }
                                        //exit(var_dump($content_field_info));


                                switch($col){

                                    case 'id':
                                        $field_typed =  'hidden';
                                        $field_labeled = '';
                                    break;
                                    case 'content_user_id':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $field_value = 'guest';
                                        $field_disable = 'READONLY';
                                        $field_style = 'color: #124e8a;border:solid 1px black;background-color: #eaeaea;';
                                    break;
                                    case 'content_id':
                                        $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                    case 'content_machine_id':
                                        $field_label = $content_field_info[$col ]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $field_value =  $type_info['content_type_name'].'-'.hash('crc32', $cck->_path_segment(1).time() . mt_rand()) .'-user';
                                        $field_disable = 'READONLY';
                                        $field_style = 'color: #124e8a;border:solid 1px black;background-color: #eaeaea;';
                                    break;
                                    case 'content_name':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $field_value =  $type_info['content_type_name'].'-'.hash('crc32', $cck->_path_segment(1).time() . mt_rand()) .'-user';
                                        $field_disable = 'READONLY';
                                        $field_style = 'color: #124e8a;border:solid 1px black;background-color: #eaeaea;';
                                    break;
                                    case 'content_container_id':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $field_value =  'container-'.hash('crc32', $type_info['content_type_name'].time() . mt_rand()) .'-'.$type_info['content_type_name'];
                                        $field_disable = 'READONLY';
                                        $field_style = 'color: #124e8a;border:solid 1px black;background-color: #eaeaea;';
                                    break;
                                    case 'content_body':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $field_value =  $type_info['content_type_name'] .' - content fields';
                                        $field_disable = 'DISABLED';
                                        $field_style = 'color: #124e8a;border:solid 2px red;background-color: #eaeaea;';
                                    break;
                                    case 'content_parent_id':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                    case 'content_css_inline':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                    case 'content_css_sheet':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                    case 'content_js':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $field_value =  '0';
                                        $field_disable = '';
                                        $field_style = 'color: #124e8a;border:solid 1px black;background-color: #eaeaea;';
                                    break;
                                    case 'content_title':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $field_value =  ''. $type_info['content_type_name'] .' post -'. date("Y-m-d H:i:s");
                                        $field_disable = 'REQUIRED';
                                        $field_style = 'color: #124e8a;border:solid 2px #f31111;background-color: #cfe5f1;';
                                        $field_style_sheet = '';
                                        $details = 'required';
                                        $details_message = 'This field is required a temporary title has been supplied for you';
                                    break;
                                    case 'content_type_id':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $field_value =  $type_info['content_type_id'];
                                        $field_disable = 'READONLY';
                                        $field_style = 'color: #124e8a;border:solid 1px black;background-color: #eaeaea;';
                                    break;
                                    case 'content_time_created':
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $field_value = date("Y-m-d H:i:s");
                                        $field_disable = 'READONLY';
                                        $field_style = 'color: #124e8a;border:solid 1px black;background-color: #eaeaea;';
                                    break;
                                    case 'content_status':

                                        $field_label = $content_field_info[$col] ['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $resultFields = $db->query('SELECT * FROM content_type_fields WHERE content_type_id="0"');
                                        while ($tField = $resultFields->fetchArray(SQLITE3_ASSOC)) {

                                            $option_list = "\n" . '<div class="col">' .$tField['title'].'</div><div class=""><select class="'.$tField['css_sheet'].'" style="color: #124e8a;'.$tField['css_inline'].'" type="'.$tField['field_type'].'" name="content_status" value="" >';
                                        
                                           
                                        


                                        $resultFieldsOptions = $db->query('SELECT * FROM content_type_field_options WHERE content_type_field_id="0"');
                                        
                                    

                                        
                                                while ($fOption = $resultFieldsOptions->fetchArray(SQLITE3_ASSOC))
                                                {

                                                    $option_list .= "\n".'<option value="'. $fOption['option_value'] .'" name="name-'.$fOption['option_html_name'].'-'.$fOption['option_machine_id'].'" id="id-'.$fOption['option_html_id'].'-'.$fOption['option_machine_id'].'">'. $fOption['option_label'] . '</option>';

                                                }

                                                
                                            }

                                        $option_list .= "\n".'</select></div>';
                                        
                                    break;
                                    case 'content_category_id':
                                        
                                        $field_label = $content_field_info[$col]['field_label'];
                                        $field_desc = $content_field_info[$col]['field_description'];
                                        $resultFields = $db->query('SELECT * FROM content_type_fields WHERE content_type_id="101"');
                                        while ($tField = $resultFields->fetchArray(SQLITE3_ASSOC)) {

                                            $cat_list = "\n" . '<div class="col">' .$tField['title'].'</div><div class=""><select class="'.$tField['css_sheet'].'" style="color: #124e8a;'.$tField['css_inline'].'" type="'.$tField['field_type'].'" name="content_category_id" value="" >';
                                        
                                           
                                        


                                        $resultFieldsOptions = $db->query('SELECT * FROM categories');
                                        
                                    

                                        
                                                while ($fOption = $resultFieldsOptions->fetchArray(SQLITE3_ASSOC))
                                                {

                                                    $cat_list .= "\n".'<option value="'. $fOption['id'] .'" name="category-'.$fOption['name'].'">'.$fOption['name'].'</option>';

                                                }

                                                
                                            }

                                        $cat_list .= "\n".'</select></div>';
                                        
                                    break;
                                }

                                
                                
                               
                                 
                                if($col == 'content_status'){
                                   
                                            $button_0 .= "\n".'<div class="row" style="">'.$option_list.'</div>';
                                            $button_0 .= '<details style="background-color: #000000; color: #ffffff;padding: 3px;"><summary>description</summary><p style="padding:3px;background-color: #ffffff;color:black;">'.$field_desc.'</p></details>';

                                }elseif($col == 'id'){

                                    continue;
                                }

                            elseif($col == 'content_category_id'){

                                            $button_0 .= "\n".'<div class="row" style="">'.$cat_list.'</div>';
                                            $button_0 .= '<details style="background-color: #000000; color: #ffffff;padding: 3px;"><summary>description</summary><p style="padding:3px;background-color: #ffffff;color:black;">'.$field_desc.'</p></details>';

                            }
                                    
                                 else {

                                   
                                            $details = 'description';
                                            $details_message = 'instructions on use';
                                            $button_0 .= '';
                                            $button_0 .= "\n".'<label style="min-width:180px;padding:3px 6px">' .$field_label.'</label><input class="'.$field_style_sheet.'" style="'.$field_style.'" type="'.$field_typed.'" name="'.$col.'" value="'.$field_value.'" '.$field_disable.' />';
                                            $button_0 .= '<details style="background-color: #000000; color: #ffffff;padding: 3px;"><summary>'.$details.'</summary><p style="padding:3px;background-color: #ffffff;color:black;">'.$field_desc.'</p></details>';

                                    
                                }
                                    
                                

                }
                            $button_0 .= "\n".'' ."\n";
                            
                        

        
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
        $view_content = $_GET;
        $view_id = $cck->_path_segment(2);
        $menu = $cck->_hooks('hook_links');
        $variables['page_title'] = 'View One';
        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);

        
        $output = print_r($view_content, true);
        $output .= print_r($view_id, true);


        $variables['content_title'] = 'View Content';
        $variables['content'] =  $output;
        print $cck->_view('default', $variables);
    }

    public function edit()
    {
        global $cck, $ini_settings;
        $menu = $cck->_hooks('hook_links');
        $variables['page_title'] = 'View One';
        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);

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

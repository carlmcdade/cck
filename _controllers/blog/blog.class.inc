<?php

namespace blog;

use SQLite3;

// classes used // classes used by the global $cck object from the globalspace


/**
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT
 *
 * @link http://hardcopy.free.nf
 * =============================
 *
 * blog.class.inc
 *
 * =============================
 * This CCK example site is built
 * around this blogging module.
 * It handles the blog content
 * type.
 *
 *
 */
class blog
{
    private $common;
    public $menu;
    public $section;
    public $module;

    public const   DUMMY = 'DUMMY';

    public function __construct()
    {
        //Test the Common settings
        $this->module = __NAMESPACE__;
    }

    /**
    *   Navigation hook for all modules
    *   the array keys appear as $variables in the template file for links
    *   link.tpl.php, spaces will be replaced by underscores.
    */

    public function __destruct()
    {
        //
    }

    public function hook_links()
    {
        $link = 'links';

        $var[$link][1] = array(
                'text' => 'Blogs',
                'path' => $this->module . '/blog_latest',
                'css_class' => array($this->module, 'main_item'),
                'css_id' => $this->module
                );
        return $var;
    }

    /**
    *   Sub navigation is a hook and displayed per call by hook_links
    */

    public function hook_module_links($index = 0)
    {

        $link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Users',
                    'path' => $this->module . '/blog_list_users',
                    'css_class' => array($this->module, 'main_item'),
                    'css_id' => $this->module
                    );
        $var[$link][2] = array(
                    'text' => 'Categories',
                    'path' => $this->module . '/blog_categories',
                    'css_class' => array($this->module, 'main_item'),
                    'css_id' => $this->module
                    );
        $var[$link][3] = array(
                    'text' => 'Content',
                    'path' => $this->module . '/blog_list_content',
                    'css_class' => array($this->module, 'main_item'),
                    'css_id' => $this->module
                    );
        $var[$link][4] = array(
                    'text' => 'Create',
                    'path' => 'content/content_types',
                    'css_class' => array($this->module, 'main_item'),
                    'css_id' => $this->module

        );



        return $var;
    }

    public function hook_access()
    {
        $authorize = array(
                $this->module . '/blog_post_add' => array('access foo'),
                $this->module . '/blog_post_edit' => array('access baz'),
                $this->module . '/blog_post_delete' => array('access boo'),
                );
        return $authorize;
    }

    public function blog_list_users()
    {
        global $cck, $ini_settings;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'View blog';
        $variables['pageTitle'] = 'Blogs';
        $variables['contentTitle'] = 'Users';
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

        $result = $db->query('SELECT * FROM userlist');

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
        $output = $cck->_view('table_user_cp', $table);
        // check for user id no id means site owner
        $variables['userID'] = $cck->_path_segment(2);
        if (empty($cck->_path_segment(2))) {
            $variables['profileImage'] = 'default_user.jpeg';
            $variables['userHandle'] = 'Site Members';
            $variables['userBio'] = $cck->_view('default_content', $variables);

        } else {

            foreach ($rows as $key => $value) {

                $variables['profileImage'] =  $value ['image'];
                $variables['userHandle'] =  $value ['name'];
                $variables['userBio'] = $value['bio'];
            }
        }


        $variables['content'] =  $output;

        print $cck->_view('page_blog_view', $variables);


    }


    public function blog_list_content()
    {
        global $cck, $ini_settings;



        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';

        //$connect = $cck->_dbconnect($ini_settings['databases']['user_db']);

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $variables = array();
        $variables['pageTitle'] = 'Blog';
        $variables['menuTitle'] = 'Blog ';
        $variables['dbTable'] = 'userlist';
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
        $userID = $cck->_path_segment(2);
        if (!empty($userID)) {
            $result = $db->query('SELECT userlist.name,userlist.bio, userlist.image,content.* FROM userlist , content WHERE userlist.id='.$userID.' AND content.content_user_id ='. $userID);
            //$result = $db->query('SELECT * FROM content WHERE id='.$userID.'');


        } else {
            $result = $db->query('SELECT userlist.name, userlist.bio, userlist.image,content.* FROM userlist , content WHERE userlist.id = content.content_user_id');

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



        //var_dump($rows);
        // check for user id no id means site owner
        $variables['userID'] = $userID;
        if (empty($cck->_path_segment(2))) {
            $variables['profileImage'] = 'default_user.jpeg';
            $variables['userHandle'] = 'Site Members';
            $variables['userBio'] = $cck->_view('default_content', $variables);
            $variables['contentTitle'] = 'Content';

        } elseif (!empty($rows)) {

            foreach ($rows as $key => $value) {

                $variables['profileImage'] =  $value ['image'];
                $variables['userHandle'] =  $value ['name'];
                $variables['userBio'] = $value['bio'];
                $variables['contentTitle'] = $value['name'] .'\'s Blog';
            }
        } else {

            /**$table['rows'] = array(array(
            	'content_body'=>'user has nothing in database yet',
            	'content_title' => 'No titles',
            	'name' => $userID
            	));*/
            $result = $db->query('SELECT userlist.* FROM userlist WHERE id='. $userID);

            while ($row = $result->fetchArray()) {
                $rows[] = $row;
            }
            foreach ($rows as $key => $value) {

                $variables['profileImage'] =  $value ['image'];
                $variables['userHandle'] =  $value ['name'];
                $variables['userBio'] = $value['bio'];
                $variables['contentTitle'] = $value['name'] .'\'s Blog';

            }

        }

        $output .= $cck->_view('table_blog_content', $table);

        //$variables['userHandle'] = $rows[0]['name'];
        //$variables['contentTitle'] = $variables['userHandle'].'\'s Blog';
        $variables['defaultContent'] = $cck->_view('default_content', $variables);
        $variables['content'] =  '<!--User Id: ' .$variables['userID']. '- '. $variables['userHandle'] . '- ' .$variables['profileImage'].'--><br>' . $output;
        print $cck->_view('page_blog_view', $variables);

    }

    public function blog_categories()
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
        $variables['pageTitle'] = 'Blog';
        $variables['menuTitle'] = 'View blog';
        $variables['contentTitle'] = 'Categories';
        $variables['dbTable'] = 'categories';


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
        $output = $cck->_view('table_user_cp', $table);



        $variables['content'] = $output;

        print $cck->_view('default', $variables);
    }

    public function blog_latest()
    {
        global $cck, $ini_settings,$_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';

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
        
        $resultContent = $db->query('SELECT * FROM content INNER JOIN content_types ON content.content_type_id = content_types.content_type_id');
        $row_count = 1;
        $content_rows = array();
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
        
        while ($row = $resultContent->fetchArray(SQLITE3_ASSOC)) {
               
                //$content_rows[$row['content_machine_id']] = $row;
                //$col = $resultContent->columnName($row_count);
                for ($i = 0; $i < $resultContent->numColumns(); $i++) {
                $col_name = $resultContent->columnName($i);
                if($col_name == 'id'){ continue; }
                $resultFieldAttr = $db->query('SELECT * FROM content_field_attributes WHERE field_container_id="'.$col_name.'"');
                    while($attributes = $resultFieldAttr->fetchArray(SQLITE3_ASSOC))
                    {
                        $field_attr[$col_name] = $attributes;
                    }
                }
                

            

                    $row_count = $row_count + 1;
                    $resultTypeFields = $db->query('SELECT * FROM content_type_fields INNER JOIN 
                    content_types ON content_type_fields.content_type_id = content_types.content_type_id WHERE 
                    content_type_fields.content_type_id="'.$row['content_type_id'].'"');
                    while($fields = $resultTypeFields->fetchArray(SQLITE3_ASSOC))
                    {
                        $content_fields[$row['content_type_id']][$fields['name']] = $fields;
                    }
                    if(unserialize($row['content_body']) == '')
                    {
                        $row['content_body'] = $content_fields;

                    } else{

                        $row['content_body'] = unserialize($row['content_body']);

                    }
                
                   // $row['content_body'] = unserialize($row['content_body']);
                    $variables['row_attributes'] = $field_attr;
                    $variables['row'] = $row;
                    $variables['content_fields'] = $content_fields;
                    $output .= $cck->_view($row['content_template'].'_content_template',$variables);
           
        }

        
        


        //var_dump($rows);
        

        //$variables['sideBar'] = $cck->_view('table_blog_latest_content', $table_posts);
        $variables['content_rows'] = $content_rows;
        $variables['content_fields'] = $content_fields;
        

        $variables['content'] = $output;//<pre>'. print_r($content_rows,1) .'</pre>';

        print $cck->_view('page_blog_latest', $variables);

    }



    public function blog_post_view()
    {
        print 'blog post view';
    }

    public function blog_post_edit()
    {

        global $cck,$ini_settings;
        $output = 'blog post edit';

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');

        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links(
            $sub_menu[$this->module],
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                )
        );
        $variables['page_title'] = 'Blog';
        $variables['content_title'] = 'Post edit';
        $variables['content'] = $output;
        print $cck->_view('default', $variables);
    }


    public function blog_post_add()
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
                'css_id' => $this->module,
                'css_class' => array($this->module)),
            $variables
        );

        $db = new SQLite3($database);


        $userID = $cck->_path_segment(2);
        if (!empty($typeID)) {
            $result = $db->query('SELECT * FROM content_types WHERE id='.$typeID.'');
        } else {
            $result = $db->query('SELECT * FROM content_types');
        }

        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }
        //SQLite3Result::numColumns();
        for ($i = 0; $i < 3; $i++) {
            $col = $result->columnName($i);
            $columns[] = $col;
        }
        $table['header'] = $columns;
        $table['rows'] = $rows;
        $output = $cck->_view('table_content_add', $table);

        foreach ($rows as $key => $value) {
            $variables['userBio'] =  '';
            $variables['userName'] = $value['name'];
            $variables['profileImage'] = '';
            $variables['userID'] = '';
        }

        $variables['content'] = 'Content types' . $output;

        print $cck->_view('default', $variables);
    }


    public function blog_post_delete()
    {
        print 'blog post delete';
    }

}

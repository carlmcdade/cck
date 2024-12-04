<?php

namespace users;

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
 *                        users.class.inc
 *
 * ==================================================================
 *
 * @todo
 *
 */


use SQLite3;

class users
{
    private $common;
    public $menu;
    public $section;
    public $module;

    public function __construct()
    {
        //Test the Common settings
        $this->module = __NAMESPACE__;

    }

    /**
     *
     * @return multitype:multitype:string
     */

    public function hook_access()
    {
        $authorize = array(
                $this->module . '/user_profile' => array('users profile'),
                $this->module . '/user_settings' => array('users settings'),
                $this->module . '/user_control_panel' => array('users control panel'),
                $this->module . '/user_history' => array('users history'),
        );
        return $authorize;
    }

    /**
    *   Navigation hook for all modules
    */

    public function hook_links()
    {
        $link = 'links';

        $var[$link][1] = array(
                'text' => 'Your Account',
                'path' => $this->module . '/user_control_panel',
                'controller' => 'page_users_profile',
                'action' => 'users_control_panel',
                'css_class' => array($this->module, 'main_item'),
                'css_id' => $this->module
                );
        return $var;
    }

    /**
    *   Sub navigation is a hook and displayed per call by hook_links
    */

    public function hook_module_links()
    {
        
		global $cck, $ini_settings;

		$link = 'links';

        $var = array();

        $var[$link][1] = array(
                    'text' => 'Profiles',
                    'path' => 'users/user_profile',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Accounts',
                    'path' => 'users/user_account',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Content',
                    'path' => 'users/user_content',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                    'text' => 'Messages',
                    'path' => 'users/user_messages',
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
        );


        return $var;
    }

    /**
     *
     *
     */

    public function user_profile()
    {
        global $cck, $ini_settings;



        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();

        //$connect = $cck->_dbconnect($ini_settings['databases']['user_db']);

        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $variables = array();
        $variables['pageTitle'] = 'Users';
        $variables['menuTitle'] = 'User Panel';
        $variables['dbTable'] = 'userlist';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['sub_navigation'] = $cck->_module_links(
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

        /*==============================================
                   content  template
        ===============================================*/
        $output = $cck->_view('table_profile_edit', $table);


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



        $variables['contentTitle'] = $variables['userHandle'].'\'s profile';
        $variables['content'] =  '<h3><i>Quick Edit</i></h3>' . $output;

        /*==============================================
                   page  template
        ===============================================*/
        print $cck->_view('page_users_profile', $variables);
    }

    /**
     *
     *
     */

    public function user_control_panel()
    {
        // set links
        global $cck,$ini_settings;


        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output ='';
        $msg = 'messages : ';


        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $user_menu = $cck->_hooks('hook_user_links');
        $variables = array();


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
        $output = $cck->_view('table_user_cp', $table);

        // Get the content column values
        $variables['userID'] = $cck->_path_segment(2);
        if (empty($cck->_path_segment(2))) {
            $variables['profileImage'] = 'default_user.jpeg';
            $variables['userHandle'] = 'Site Members';
            $variables['menuTitle'] = 'User';

            $link = 'links';

            $var = array();

            $var[$link][1] = array(
                        'text' => 'Profiles',
                        'path' => 'users/user_profile',
                        'css_id' => $this->module.'-1',
                        'css_class' => array($this->module.'_1')
                        );
            $var[$link][2] = array(
                        'text' => 'Accounts',
                        'path' => 'users/user_account',
                        'css_id' => $this->module.'-2',
                        'css_class' => array($this->module.'_2')
                        );
            $var[$link][3] = array(
                        'text' => 'Content',
                        'path' => 'content/content_user_list',
                        'css_id' => $this->module.'-3',
                        'css_class' => array($this->module.'_3')
                        );
            $var[$link][4] = array(
                        'text' => 'Settings',
                        'path' => 'users/user_settings',
                        'css_id' => $this->module.'-4',
                        'css_class' => array($this->module.'_4')
                        );



        } else {

            foreach ($rows as $key => $value) {

                $variables['profileImage'] =  $value ['image'];
                $variables['userHandle'] =  $value ['name'];
                $variables['userBio'] = $value['bio'];
                $variables['menuTitle'] = $value['name'];
            }

            $link = 'links';

            $var = array();

            $var[$link][1] = array(
                        'text' => 'Profile',
                        'path' => 'users/user_profile/' . $userID,
                        'css_id' => $this->module.'-1',
                        'css_class' => array($this->module.'_1')
                        );
            $var[$link][2] = array(
                        'text' => 'Accounts',
                        'path' => 'users/user_account/' . $userID,
                        'css_id' => $this->module.'-2',
                        'css_class' => array($this->module.'_2')			);
            $var[$link][3] = array(
                        'text' => 'Content',
                        'path' => 'users/user_blog/' . $userID,
                        'css_id' => $this->module.'-3',
                        'css_class' => array($this->module.'_3')
                        );
            $var[$link][4] = array(
                    'text' => 'Settings',
                    'path' => 'users/user_settings/' . $userID,
                    'css_id' => $this->module.'-4',
                    'css_class' => array($this->module.'_4')
            );


        }
        $variables['pageTitle'] = 'User Control Panel';
        $variables['contentTitle'] = 'Users';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $var,
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => 'submenu-' .$this->module,
                'css_class' => array('submenu_'. $this->module)
                ),
            $variables
        );

        $variables['content'] = $output;
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';

        $msg .= "";
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName']:'');
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_cp', $variables);
    }

    /**
     *
     *
     */

    public function user_settings()
    {
        // get all links from each class controller
        global $cck, $ini_settings;


        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();


        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $user_menu = $cck->_hooks('hook_user_links');
        $variables['pageTitle'] = 'User';
        $variables['contentTitle'] = 'User settings';

        $variables['menuTitle'] = 'User Settings';
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
        $output = $cck->_view('table_user_cp', $table);




        $variables['content'] = $output;
        print $cck->_view('page_users_cp', $variables);
    }

    /**
     *
     *
     */

    public function user_history()
    {
        // get all links from each class controller
        global $cck, $ini_settings;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();


        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $variables = array();
        $variables['pageTitle'] = 'User History';
        $variables['contentTitle'] = 'User History';
        $variables['dbTable'] = 'userlist';
        $variables['menuTitle'] = 'User History';
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
        // get user id from url


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



        $variables['content'] = $output;
        print $cck->_view('page_users_profile', $variables);
    }

    /**
     *
     *
     */

    public function users_login_submit()
    {
        $variables['content'] = 'show users logged in and redirect';
        print $cck->_view('page_users_profile', $variables);
    }

    /**
     *
     *
     */

    public function users_login_form()
    {
        $variables['content'] = 'show users login form';
        print $cck->_view('page_users_profile', $variables);
    }

    public function user_account($userID = null)
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
        $output = $cck->_view('table_user_cp', $table);
        // Get the content column values
        $variables['userID'] = $cck->_path_segment(2);
        if (empty($cck->_path_segment(2))) {
            $variables['profileImage'] = 'default_user.jpeg';
            $variables['userHandle'] = 'Site Members';
            $variables['menuTitle'] = 'Site Users';

            $link = 'links';

            $var = array();

            $var[$link][1] = array(
                        'text' => 'User Profiles',
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
                        'path' => 'users/user_content',
                        'css_id' => $this->module,
                        'css_class' => array($this->module)
                        );
            $var[$link][4] = array(
                        'text' => 'User Settings',
                        'path' => 'users/user_settings',
                        'css_id' => $this->module,
                        'css_class' => array($this->module)
            );



        } else {

            foreach ($rows as $key => $value) {

                $variables['profileImage'] =  $value ['image'];
                $variables['userHandle'] =  $value ['name'];
                $variables['userBio'] = $value['bio'];
                $variables['menuTitle'] = $value['name'];
            }
        }


        $variables['pageTitle'] = 'Users';
        $variables['contentTitle'] = 'User Accounts';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $var,
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                ),
            $variables
        );

        $variables['content'] = $output;

        print $cck->_view('page_users_cp', $variables);

    }

    public function user_blog($userID = null)
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

        $variables['content'] = "User Acoount: ". $output;

        print $cck->_view('page_users_cp', $variables);

    }

    public function user_content($userID = null)
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
        $variables['menuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Users';
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
        $output = $cck->_view('table_user_cp', $table);



        $variables['content'] =  $output;

        print $cck->_view('page_users_cp', $variables);

    }

    public function user_messages($userID = null)
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
        $userID = $cck->_path_segment(2);

        $result = $db->query('SELECT * FROM userlist WHERE id="' . $userID. '"');

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

        $variables['content'] = "User Messages: ". $output;

        print $cck->_view('page_users_cp', $variables);

    }
    /**
     *
     *
     */

    public function users_logout_submit()
    {
        $variables['content'] = 'show users logged out and redirect';
        print $cck->_view('page_users_profile', $variables);
    }

    /**
     *
     *
     */

    public function users_logout()
    {
        $variables['content'] = 'show users logout confirmation';
        print $cck->_view('page_users_profile', $variables);
    }

    public function edit_user($userID = null)
    {

        /* ====================== Method variables ===============*/
        global $cck,$ini_settings;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';

        /// build admin navigation links that only are used by this module/method

        /* ====================== navigation menus ===============*/
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
        $var[$link][5] = array(
                'text' => 'Settings',
                'path' => 'users/edit_user_settings/'.$userID,
                'css_id' => $this->module,
                'css_class' => array($this->module)
                    );



        /* ====================== template variables ===============*/
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $admin_menu = $var;

        /* ====================== database query ===============*/
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

        /* ====================== content template ===============*/
        $output = $cck->_view('table_user_edit', $table);

        foreach ($rows as $key => $value) {
            $variables['userBio'] =  $value['bio'];
            $variables['userName'] = $value['name'];
            $variables['profileImage'] = $value['image'];
            $variables['userID'] = $userID;
        }

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Members';
        $variables['adminMenuTitle'] = $variables['userName'];
        $variables['pageTitle'] = 'User Admin';
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

        $variables['content'] = $output;
        /* ====================== page template ===============*/
        print $cck->_view('page_users_cp', $variables);

    }


    public function edit_profile($userID = null)
    {
        global $cck,$ini_settings;
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
                    'path' => 'users/edit_profile/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][2] = array(
                    'text' => 'Account',
                    'path' => 'users/edit_user/'.$userID,
                    'css_id' => $this->module,
                'css_class' => array($this->module)
                    );
        $var[$link][3] = array(
                    'text' => 'Content',
                    'path' => 'users/edit_post/'.$userID,
                    'css_id' => $this->module,
                    'css_class' => array($this->module)
                    );
        $var[$link][4] = array(
                'text' => 'Settings',
                'path' => 'users/edit_user_settings/'.$userID,
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );
        $var[$link][5] = array(
                'text' => 'Inbox',
                'path' => 'users/edit_messages/' .$userID,
                'css_id' => $this->module,
                'css_class' => array($this->module)
        );



        $sub_menu = $cck->_hooks('hook_module_links');
        $menu = $cck->_hooks('hook_links');
        $admin_menu = $var;

        /*================= database  query ========================*/
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


        foreach ($rows as $key => $value) {
            $variables['userBio'] =  $value['bio'];
            $variables['userName'] = $value['name'];
            $variables['profileImage'] = $value['image'];
            $variables['userID'] = $userID;
        }

        //var_dump($sub_menu); exit;
        $variables['menuTitle'] = 'Members';
        $variables['adminMenuTitle'] = $variables['userName'];
        $variables['pageTitle'] = 'User Admin';
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

        $variables['content'] = $output;
        /*==============================================
                   page  template
        ===============================================*/
        print $cck->_view('page_users_profile', $variables);

    }

    public function edit_user_save()
    {
        $link = 'links';


        global $cck,$ini_settings;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $var = array();
        $output = '';


        $var = array();

        $var[$link][1] = array(
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
        $variables['content'] =  $output;

        print $cck->_view('page_users_cp', $variables);

    }


    public function edit_profile_save()
    {
        global $cck,$ini_settings;
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
        $variables['content'] =  $output;

        print $cck->_view('page_users_profile', $variables);

    }
}

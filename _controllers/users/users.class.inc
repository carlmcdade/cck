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
use DateTime;

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

        // get all links from each class controller
        global $cck, $ini_settings,$_SESSION;
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';
        //exit('<pre>'.var_dump($_SESSION));

        $userID = (isset($_SESSION['UserData']['user_id']) ? $_SESSION['UserData']['user_id'] : '0');
        $link = 'links';

        $var[$link][1] = array(
            'text' => 'Events',
            'path' => $this->module . '/user_calendar/'. $userID,
            'controller' => 'page_users_profile',
            'action' => 'users_control_panel',
            'css_class' => array($this->module, 'main_item'),
            'css_id' => $this->module
            );
        $var[$link][2] = array(
                'text' => 'Your Account',
                'path' => $this->module . '/user_control_panel/'. $userID,
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

        // get all links from each class controller
        global $cck, $ini_settings,$_SESSION;
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

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
        global $cck, $ini_settings,$_SESSION;



        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_profile', $variables);
    }

    /**
     *
     *
     */

    public function user_control_panel()
    {
        // set links
        global $cck,$ini_settings,$_SESSION;


        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $var = array();
        $output = '';
        $msg = 'messages : ';
        $link = 'links';


        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $user_menu = $cck->_hooks('hook_user_links');
        $variables = array();


        $db = new SQLite3($database);

        $userID = (isset($_SESSION['UserData']['user_id']) ? $_SESSION['UserData']['user_id'] : $cck->_path_segment(2));


        if (!empty($userID) && $userID == $cck->_path_segment(2)) {
            $result = $db->query('SELECT * FROM userlist WHERE user_id='.$userID.'');
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
        $variables['userID'] = (isset($_SESSION['UserData']['user_id']) ? $_SESSION['UserData']['user_id'] : $cck->_path_segment(2));


        if ((!empty($userID)) and ($userID >= 0)) {
            $variables['profileImage'] = 'default_user.jpeg';
            $variables['userHandle'] = 'Site Members';
            $variables['menuTitle'] = (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : 'User');

            $userID = (isset($_SESSION['UserData']['user_id']) ? $_SESSION['UserData']['user_id'] : '00');

            $var_u = array();
            $userID = (isset($_SESSION['UserData']['user_id']) ? $_SESSION['UserData']['user_id'] : 'guest');

            $var_u[$link][1] = array(
                        'text' => 'Profile',
                        'path' => 'users/user_profile/' . $userID,
                        'css_id' => $this->module.'-1',
                        'css_class' => array($this->module.'_1')
                        );
            $var_u[$link][2] = array(
                        'text' => 'Accounts',
                        'path' => 'users/user_account/' . $userID,
                        'css_id' => $this->module.'-2',
                        'css_class' => array($this->module.'_2'));
            $var_u[$link][3] = array(
                        'text' => 'Content',
                        'path' => 'users/user_blog/' . $userID,
                        'css_id' => $this->module.'-3',
                        'css_class' => array($this->module.'_3')
                        );
            $var_u[$link][4] = array(
                        'text' => 'Calendar',
                        'path' => 'users/user_calendar/'. $userID,
                        'css_id' => $this->module.'-3',
                        'css_class' => array($this->module.'_4')
                        );
            $var_u[$link][5] = array(
                        'text' => 'Settings',
                        'path' => 'users/user_settings/'. $userID,
                        'css_id' => $this->module.'-4',
                        'css_class' => array($this->module.'_5')
                        );

            $sub_menu = $var_u;


            $var_ad = array();
            $userID = '0';
            $link = 'links';
            $var_ad[$link][1] = array(
                        'text' => 'Profile',
                        'path' => 'admin/admin_user_profiles/' . $userID,
                        'css_id' => $this->module.'-1',
                        'css_class' => array($this->module.'_1')
                        );
            $var_ad[$link][2] = array(
                        'text' => 'Accounts',
                        'path' => 'admin/admin_user_accounts/' . $userID,
                        'css_id' => $this->module.'-2',
                        'css_class' => array($this->module.'_2'));
            $var_ad[$link][3] = array(
                        'text' => 'Content',
                        'path' => 'admin/admin_user_content/' . $userID,
                        'css_id' => $this->module.'-3',
                        'css_class' => array($this->module.'_3')
                        );
            $var_ad[$link][4] = array(
                    'text' => 'Settings',
                    'path' => 'admin/admin_user_settings/' . $userID,
                    'css_id' => $this->module.'-4',
                    'css_class' => array($this->module.'_4')
            );

            $admin_menu = $var_ad;


        } else {
            /* set menu to admin mode using zero '0' user id*/
            $variables['menuTitle'] = (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : 'Guest User');


            $var_u = array();
            $userID = (isset($_SESSION['UserData']['user_id']) ? $_SESSION['UserData']['user_id'] : 'guest');

            $var_u[$link][1] = array(
                        'text' => 'Profile',
                        'path' => 'users/user_profile/' . $userID,
                        'css_id' => $this->module.'-1',
                        'css_class' => array($this->module.'_1')
                        );
            $var_u[$link][2] = array(
                        'text' => 'Accounts',
                        'path' => 'users/user_account/' . $userID,
                        'css_id' => $this->module.'-2',
                        'css_class' => array($this->module.'_2'));
            $var_u[$link][3] = array(
                        'text' => 'Content',
                        'path' => 'users/user_blog/' . $userID,
                        'css_id' => $this->module.'-3',
                        'css_class' => array($this->module.'_3')
                        );
            $var_u[$link][4] = array(
                        'text' => 'Calendar',
                        'path' => 'users/user_calendar/'. $userID,
                        'css_id' => $this->module.'-3',
                        'css_class' => array($this->module.'_4')
                        );
            $var_u[$link][5] = array(
                        'text' => 'Settings',
                        'path' => 'users/user_settings/'. $userID,
                        'css_id' => $this->module.'-4',
                        'css_class' => array($this->module.'_5')
                        );

            $sub_menu = $var_u;


            $var_ad = array();
            $userID = '0';
            $link = 'links';
            $var_ad[$link][1] = array(
                        'text' => 'Profile',
                        'path' => 'admin/admin_user_profiles/' . $userID,
                        'css_id' => $this->module.'-1',
                        'css_class' => array($this->module.'_1')
                        );
            $var_ad[$link][2] = array(
                        'text' => 'Accounts',
                        'path' => 'admin/admin_user_accounts/' . $userID,
                        'css_id' => $this->module.'-2',
                        'css_class' => array($this->module.'_2'));
            $var_ad[$link][3] = array(
                        'text' => 'Content',
                        'path' => 'admin/admin_user_content/' . $userID,
                        'css_id' => $this->module.'-3',
                        'css_class' => array($this->module.'_3')
                        );
            $var_ad[$link][4] = array(
                    'text' => 'Settings',
                    'path' => 'admin/admin_user_settings/' . $userID,
                    'css_id' => $this->module.'-4',
                    'css_class' => array($this->module.'_4')
            );

            $admin_menu = $var_ad;



        }
        /*
                    foreach ($rows as $key => $value) {

                        $variables['profileImage'] =  $value ['image'];
                        $variables['userHandle'] =  $value ['name'];
                        $variables['userBio'] = $value['bio'];
                        $variables['menuTitle'] = $value['name'];
                    }*/

        /* admin menu  and those without user

            $var_u = array();
            $userID = '0';
            $var_u[$link][1] = array(
                   'text' => 'Profile',
                   'path' => '?admin/user_profile/' . $userID,
                   'css_id' => $this->module.'-1',
                   'css_class' => array($this->module.'_1')
                   );
            $var_u[$link][2] = array(
                   'text' => 'Accounts',
                   'path' => '?admin/user_account/' . $userID,
                   'css_id' => $this->module.'-2',
                   'css_class' => array($this->module.'_2'));
            $var_u[$link][3] = array(
                   'text' => 'Content',
                   'path' => '?admin/user_blog/' . $userID,
                   'css_id' => $this->module.'-3',
                   'css_class' => array($this->module.'_3')
                   );
            $var_u[$link][4] = array(
               'text' => 'Settings',
               'css_id' => $this->module.'-4',
               'css_class' => array($this->module.'_4')
            );

            */



        $variables['pageTitle'] = 'Control Panel';
        $variables['contentTitle'] = 'Users';
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
        $variables['subNavigation'] = $cck->_module_links(
            $sub_menu,
            array(
                'template' => 'links_sub_menu',
                'index' => $this->module,
                'css_id' => 'submenu-' .$this->module,
                'css_class' => array('submenu_'. $this->module)
                ),
            $variables
        );

        $variables['adminMenuTitle'] = 'Members';
        $variables['adminNavigation'] = $cck->_module_links(
            $admin_menu,
            array(
            'template' => 'links_user_menu',
            'index' => $this->module,
            'css_id' => $this->module,
            'css_class' => array($this->module)
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
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
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
        global $cck, $ini_settings,$_SESSION;


        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';


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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_cp', $variables);
    }

    /**
     *
     *
     */

    public function user_history()
    {
        // get all links from each class controller
        global $cck, $ini_settings,$_SESSION;

        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';


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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_profile', $variables);
    }

    /**
     *
     *
     */

    public function users_login_submit()
    {
        // get all links from each class controller
        global $cck, $ini_settings,$_SESSION;
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

        $variables['content'] = 'show users logged in and redirect';
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_profile', $variables);
    }

    /**
     *
     *
     */

    public function users_login_form()
    {
        // get all links from each class controller
        global $cck, $ini_settings,$_SESSION;
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';


        $variables['content'] = 'show users login form';
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_profile', $variables);
    }

    public function user_account($userID = null)
    {
        // get all links from each class controller
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
        $userID = (isset($_SESSION['UserData']['user_id']) ? $_SESSION['UserData']['user_id'] : $cck->_path_segment(2));


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

            $link = 'links';

            $var = array();

            $var[$link][1] = array(
                        'text' => 'Profile',
                        'path' => 'users/user_profile/'. $userID,
                        'css_id' => $this->module,
                        'css_class' => array($this->module)
                        );
            $var[$link][2] = array(
                        'text' => 'Account',
                        'path' => 'users/user_account/'. $userID,
                        'css_id' => $this->module,
                        'css_class' => array($this->module)
                        );
            $var[$link][3] = array(
                        'text' => 'Content',
                        'path' => 'users/user_content/'. $userID,
                        'css_id' => $this->module,
                        'css_class' => array($this->module)
                        );
            $var[$link][4] = array(
                        'text' => 'Settings',
                        'path' => 'users/user_settings/'. $userID,
                        'css_id' => $this->module,
                        'css_class' => array($this->module)
            );


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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_cp', $variables);

    }

    public function user_blog($userID = null)
    {
        // get all links from each class controller
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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_cp', $variables);

    }

    public function user_content($userID = null)
    {
        // get all links from each class controller
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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_cp', $variables);

    }

    public function user_calendar()
    {


        // get all links from each class controller
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
        $variables['menuTitle'] = 'User Admin';
        $variables['pageTitle'] = 'Users';
        $variables['contentTitle'] = 'Event Calendar';
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

        /*****************  calendar  ******************* */
        $check_events = $cck->_path_segment(2);
        $year = 2025;
        $date = new DateTime("".$year."-01-01");
        $weekday = (int)$date->format('N');
        $weekn = (int)$date->format('W');
        $day = 1;
        $month = 1;

        $dayLabels = array("Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun");

        // This creates a "table head" for each month
        $thead = '<tr><th>M</th><th>W</th>';
        foreach ($dayLabels as $lbl) {
            $thead .= "<th>".$lbl."</th>";
        }
        $thead .= '</tr>';

        // This variable will hold the html table of the calendar
        $calendar = '<table id="calendar" border="1" style="width: 550px; max-width: 100%;">';

        // Loop each month until 12
        for (;$month <= 12; $month++) {
            $calendar .= $thead;
            $monthday = 1;
            $monthmax = cal_days_in_month(CAL_GREGORIAN, $month, $year);

            $month_list = array(
            1 => 'January',
            2 => 'February',
            3 => 'March',
            4 => 'April',
            5 => 'May',
            6 => 'June',
            7 => 'July',
            8 => 'August',
            9 => 'September',
            10 => 'October',
            11 => 'November',
            12 => 'December');

            $month_name = $month_list[$month];
            $position = 0;

            while ($monthday <= $monthmax) {
                // Create month and week columns
                if ($position == 0) {
                    $weekn = (int)$date->format('W');
                    $calendar .= "<tr><th>". $month_name ."</th><th>".$weekn."</th>\n";
                    $position++;
                } // Create "non-days"
                elseif ($position < $weekday) {
                    $calendar .= "<td class=\"nonday\"></td>\n";
                    $position++;
                } // Create days
                elseif ($position == $weekday) {
                    $day_name = $year."_".$month."_".$monthday;
                    $day_id = $year."-".$month."-".$monthday;
                    $event_date = (!empty($cck->_query_segment(1)) ? $cck->_query_segment(1) : '');

                    $check_events = '';

                        if (!empty($event_date) and ($day_name == $event_date)) {

                            $check_events = 'check-events';

                        } else {

                            $check_events = 'no-events';
                        }

                


                    $calendar .= '<td style="padding:0px;" class="table-cell"><a href="?users/user_calendar&event_date='.$day_name.'#'.$day_id.'" class="'.$check_events.
                    '" name="'. $day_name .'" id="'.$day_id.'" " title="'. $year.'/'.$month.'/'.$monthday.
                    '">'.$monthday. '</a></td>'. "\n";
                    $position++;
                    $weekday++;
                    $monthday++;
                    $date->modify('+1 day');

                    if ($position == 8) {
                        $position = 0;
                        $weekday = 1;
                    }
                }
            }

            // Finish "non-days"
            while ($position != 0) {
                $calendar .= "<td class=\"nonday\"></td>\n";
                $position++;
                if ($position == 8) {
                    $position = 0;
                }
            }
            $calendar .= "</tr>";
            if ($month != 12) {
                $calendar .= '<td colspan="9" class="monthlinebreak"></td>'."\n";
            }
        }
        $calendar .= '</table>'."\n\n\t";
        /******************* end calendar *********************/
        /*********************list content types for calendar events**************/

        $db = new SQLite3($database);

        $typeID = $cck->_path_segment(2);

        $resultAdd = $db->query('SELECT * FROM content_types');

        $count = 1;

        $type_forms = '';
    
        while ($rowAdd = $resultAdd->fetchArray(SQLITE3_ASSOC)) {
            $rows = array();
            $result = $db->query('SELECT * FROM content_type_fields WHERE content_type_id ="'. $rowAdd['contenttype_id'].'" ORDER BY weight asc;');
            while ($row = $result->fetchArray(SQLITE3_ASSOC)) {
                $rows[] = $row;

                $form['contentTypeFields'][] = $row; //content type fields are not  content form fields


            }

            $form['contentType'] = $rowAdd['name'];
            $form['contentTypeId'] = $rowAdd['id'];
            $form['contentUserId'] = $rowAdd['contenttype_user_id'];
            $form['contentTypeCategories'] = $rowAdd['contenttype_category_id'];

            $form['formAction'] = '?users/calendar_event_save/'. $form['contentType'];
            $form['mimeType'] = '';
            $form['header'] = $columns;
            $form['rows'] = $rows;

            $form['contentUserId'] = (isset($form['contentUserId']) ? $form['contentUserId'] : '1');
            $form['userName'] = (isset($form['userName']) ? $form['userName'] : 'owner');
            $form['contentType'] = (isset($form['contentType']) ? $form['contentType'] : '');
            $form['contentId'] = $form['contentType'].'-'.hash('crc32', $cck->_path_segment(1).time() . mt_rand()) .'-'. $form['userName'];
            
            $form['contentTime'] = date("Y-m-d H:i:s");
            $form['enumerate'] = $count;
            $type_forms .= $cck->_view('form_user_event_post', $form);
            $count = $count + 1;
        }

        $eventAdd = $db->query('SELECT * FROM calendar_events');
        while ($eventAdd = $resultAdd->fetchArray(SQLITE3_ASSOC)) {
            $rows = array();
            $field_result = $db->query('SELECT * FROM calendar_events');
            while ($row = $field_result->fetchArray(SQLITE3_ASSOC)) {

                $form_save_event['eventFields'] = $row; //content type fields are not  content form fields

            }

        } 
        
        for ($i = 0; $i < $field_result->numColumns(); $i++) {
            $col = $field_result->columnName($i);
            $columns[$col] = $col;
        }
        $form_event['eventFields'] = $columns; //content type fields are not  content form fields

      

        $variables['contentTypes'] = $type_forms;
        
        $form_event['contentType'] = '';
        $form_event['contentTypeId'] = '';
        $form_event['contentUserId'] = 'content user id';
        $form_event['contentTypeCategories']['category-'. $count] = 'categories';

        $form_event['formAction'] = '?users/calendar_event_save/';
        $form_event['mimeType'] = '';
        $form_event['header'] = $columns;
        $form_event['rows'] = $rows;

        $form_event['contentUserId'] = '';
        $form_event['userName'] = 'owner';
        $form_event['contentType'] = '';
        $form_event['contentId'] = '-'.hash('crc32', $cck->_path_segment(1).time() . mt_rand()) .'- event';
        $form_event['contentTypeFields'][] = $rows; //content type fields are not  content form fields

        $form_event['contentTime'] = date("Y-m-d H:i:s");
        $form_event['enumerate'] = $count;

        $form_event['CCK'] = $cck;
        $form_event['INI'] = $ini_settings;
        $form_event['VAR'] = $variables;
        $form_event = $cck->_view('form_action_event_save', $form_event);
        $variables['previewEvent'] = $form_event;

/**************    event entry form ***************/

        
        $count = 1;

        $type_forms = '';
        $form_rows = array();
        $form_event_rows = array();
        $eventAddSave = $db->query('SELECT * FROM calendar_events');
        while ($listEvent = $eventAddSave->fetchArray(SQLITE3_ASSOC)) {
            
            
            $form_event_rows[] = $listEvent;
        } 
        $field_row_result = $db->query('SELECT * FROM calendar_events');
            
            while ($field_row = $field_row_result->fetchArray()) {

                $form_save_event['eventFields'] = $field_row; //content type fields are not  content form fields
                $form_rows[] = $field_row;
                $form_save_event['eventRows'][] = $field_row;
            }
        for ($i = 0; $i < $field_row_result->numColumns(); $i++) {
            $col = $field_row_result->columnName($i);
            $columns[$col] = $col;
        }
        $form_save_event['eventFields'] = $columns; //content type fields are not  content form fields

        $form_save_event['contentType'] = '';
        $form_save_event['contentTypeId'] = '';
        $form_save_event['contentUserId'] = 'content user id';
        $form_save_event['contentTypeCategories']['category-'. $count] = 'categories';

        $form_save_event['formAction'] = '?users/calendar_event_save/';
        $form_save_event['mimeType'] = '';
        $form_save_event['header'] = $columns;
        $form_save_event['rows'] = $form_rows;
        //$form_save_event['eventRows'] = $form_event_rows;

        $form_save_event['contentUserId'] = '';
        $form_save_event['userName'] = 'owner';
        $form_save_event['contentType'] = (isset($_POST['content_type'] ) ? $_POST['content_type']: '');
        $form_save_event['contentId'] = '-'.hash('crc32', $cck->_path_segment(1).time() . mt_rand()) .'- event';
        $form_save_event['contentTypeFields'][] = $rows; //content type fields are not  content form fields

        $form_save_event['contentTime'] = date("Y-m-d H:i:s");
        $form_save_event['enumerate'] = $count;

        $form_save_event['CCK'] = $cck;
        $form_save_event['INI'] = $ini_settings;
        $form_save_event['VAR'] = $variables;
        $form_save_event = $cck->_view('form_action_event_save', $form_save_event);
        $variables['formSaveEvent'] = $form_save_event;
        
        //var_dump($rows);
        //SQLite3Result::numColumns();
        for ($i = 0; $i < $result->numColumns(); $i++) {
            $col = $result->columnName($i);
            $columns[$col] = $col;
        }


        /***************************end content types*******************/
        $table['messages'] = $msg;
        $table['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $table['CCK'] = $cck;
        $table['INI'] = $ini_settings;
        $table['VAR'] = $variables;
        $table['userCalendar'] = $calendar;
        $variables['userCalendar'] = $cck->_view('table_user_calendar', $table);

        
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['formName'] = 'form_login_user';
        $variables['postUrl'] = '?admin/login_check';
/***********event post form************/


/*** end event post form */
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        $variables['content'] = (isset($form_save_event) ? $form_save_event: 'content palace holder');
        print $cck->_view('page_users_calendar', $variables);




    }

    public function user_calendar_event()
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
        $msg = 'messages : ';


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
        $output = '<pre>'. print_r($_POST,1). '</pre>';
        $variables['content'] =  $output;
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_user_save', $variables);

    }

    public function user_messages($userID = null)
    {
        // get all links from each class controller
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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_cp', $variables);

    }
    /**
     *
     *
     */

    public function users_logout_submit()
    {

        /* ====================== Method variables ===============*/
        global $cck,$ini_settings, $_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

        $variables['content'] = 'show users logged out and redirect';
        print $cck->_view('page_users_profile', $variables);
    }

    /**
     *
     *
     */

    public function users_logout()
    {


        /* ====================== Method variables ===============*/
        global $cck,$ini_settings, $_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';

        $variables['content'] = 'show users logout confirmation';
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_profile', $variables);
    }

    public function edit_user($userID = null)
    {

        /* ====================== Method variables ===============*/
        global $cck,$ini_settings, $_SESSION;
        // get all links from each class controller
        $database = $ini_settings['databases']['user_db'];
        $table = array();
        $columns = array();
        $rows = array();
        $output = '';
        $msg = 'messages : ';


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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
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
        $msg = 'messages : ';

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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
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
        $msg = 'messages : ';


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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
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
        $msg = 'messages : ';


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
        $variables['messages'] = $msg;
        $variables['loggedInUser'] =  (isset($_SESSION['UserData']['UserName']) ? $_SESSION['UserData']['UserName'] : '');
        $variables['CCK'] = $cck;
        $variables['INI'] = $ini_settings;
        $variables['VAR'] = $variables;
        print $cck->_view('page_users_profile', $variables);

    }
}

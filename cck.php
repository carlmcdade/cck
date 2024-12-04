<?php



/**
 * Content Connection Kit
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT 1.0
 *
 * @link http://hardcopy.free.nf
 * ==================================================================
 *
 *                       cck.php
 *
 * ==================================================================
 * Bootstrap CCK
 *
 * @todo Define some constants and globals that can be easily changed. Done here because there maybe multiple modules.
 * taking care of different application sets. Start bootstrapping here.
 *
 * @todo create a more structured bootstrap file that can be used in other
 * situations
 *
*/
define('CCK_ROOT', basename(__DIR__));
define('DOCROOT', dirname(__FILE__));

define('INI_FILENAME', DOCROOT . "/_configuration/config.ini");
define('INSTALLDIR', basename(__DIR__));
//echo '<pre>' . print_r($_SERVER). '</pre>'; exit;
//define('URL_DIR', $_SERVER['REQUEST_URI']);


/*
* These global variables are necessary to carry values to the Classes nested
* in the module functions.
*
* @todo Module_list and hook_list should come from a configuration data source
* loaded by a Singleton Class
*
*/



class CCK
{
    private $ini_settings = array();
    public $common;
    public $default_main_menu = 'links_main_menu';
    public $default_admin_menu = 'links_admin_menu';
    public $_modules_list;
    public $hooks_list;
    public $moduleName;
    public $section;
    public $dbc;
    public $type = 'common';


    public function __construct()
    {
        //
        spl_autoload_register(array($this, '_autoload'));
        spl_autoload_register(array($this, '_helpers_autoload'));
        spl_autoload_register(array($this, '_frameworks_autoload'));

        if (file_exists(INI_FILENAME)) {

            $this->ini_settings =  parse_ini_file(INI_FILENAME, true);
            $this->_modules_list = $this->ini_settings['modules'];
            $this->hooks_list = $this->ini_settings['hooks'];


        }

    }

    public function __tostring()
    {
        //
        return 'cck';
    }

    public function _autoload($class)
    {
        //
        global $ini_settings;
        static $common_loaded = false;

        //CCK


        // directories
        $controllers = $ini_settings['system']['controllers'];
        $helpers = $ini_settings['system']['helpers'];

        // get a list of class file names. Allow only these and not Drupal class files in array
        $class = strtolower($class);
        $check_class = substr_count($class, '_');

        // load the modules standard controller
        if ($check_class == 0) {

            // try and load without namespace
            $path = DOCROOT . '/_controllers/'. $class . '/' . $class . '.class.inc';

            if (file_exists($path)) {
                require_once($path);
            }

            spl_autoload_register(
                function ($class) {
                    $parts = explode('\\', $class);

                    # Support for non-namespaced classes.
                    $parts[] = str_replace('_', DIRECTORY_SEPARATOR, array_pop($parts));

                    $path = implode(DIRECTORY_SEPARATOR, $parts);

                    $file = stream_resolve_include_path($path.'.class.inc');
                    if ($file !== false) {
                        require $file;
                    }
                }
            );


            $modules_loaded = true;
        }
        // load modules helper controllers and  sub classes
        elseif ($check_class > 0) {
            $list = preg_split('/_/', $class);
            $controller = $list[0];
            $hook = $list[1];
            // get the types of class files that belong to a controller module from the ini settings file
            // do a loop here to compare the values of the ini and the suffix
            $path = '';
            foreach ($ini_settings['suffixes'] as $suffix) {
                if ($hook == $suffix && $controller != 'common') {
                    //$class = strtolower(ber_pathpart(0));
                    $path = DOCROOT . '/_controllers/'. $controller . '/' . $controller . '_' . $suffix . '.class.inc';
                    if (file_exists($path)) {
                        require_once($path);
                    }
                }
            }
            $sub_modules_loaded = true;
            $modules_loaded = false;
            $debug = '';
        }

        // load module controllers that have a set namespace
        else {
            return;
        }
    }

    public function _helpers_autoload($class)
    {
        //
        $class = strtolower($class);
        $path = DOCROOT . '/_helpers/' . $class . '/' . $class . '.php';
        $path = str_replace("\\", "/", $path);

        if (file_exists($path)) {
            require_once($path);
        }
        return;
    }

    public function _frameworks_autoload($class)
    {
        //

    }

    public function _bootstrap($inclass = null, $foraction = null)
    {
        // required

        global $cck,$ini_settings;

        $controller = null;
        $action = null;
        $arguments = implode(',', func_get_args());
        $variables = $ini_settings['modules'];

        // $allow alias to load [controller]/[action] directly using bootstrap to avoid HTTP redirects
        if ($inclass && $foraction) {
            $class = $inclass;
            $action = $foraction;

        } else {
            $class = strtolower($cck->_path_segment(0));
            $action = strtolower($cck->_path_segment(1));
        }

        $menu = $cck->_hooks('hook_links');
        $access = $cck->_hooks('hook_access');

        $namespace = $class.'\\'.$class;
        $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);

        if (class_exists($class) == true || class_exists($namespace) == true) {
            // if not in a namespace then go to root class
            if (class_exists($class) == true) {
                $controller = new $class();
                if (method_exists($controller, $action)) {
                    return $controller->$action($arguments); // send string of arguments
                } else {
                    $class = str_replace('_', '/', $class);
                    $output = 'The address requested '. $class .'/'. $action.' does not exist. 1001' ;
                    $variables['contentTitle'] = 'ERROR : ' . $cck->_path_segment(1);
                    $variables['content'] = $output;
                    print $cck->_view('page_404', $variables);
                    exit('');
                }
            } elseif (class_exists($namespace) == true) {
                $controller = new $namespace();
                if (method_exists($controller, $action)) {
                    return $controller->$action($arguments); // send string of arguments
                } else {
                    $output = 'The address requested '. $class .'/'. $action.' does not exist.';
                    $variables['contentTitle'] = 'ERROR : ' . $cck->_path_segment(1);
                    $variables['content'] = $output;
                    print $cck->_view('page_404', $variables);
                    exit('');
                }
            } else {
                $output = 'The site address requested does not exist.'. $action ;
                $variables['contentTitle'] = 'ERROR : ' . $cck->_path_segment(1);
                $variables['content'] = $output;
                print $cck->_view('page_404', $variables);
                exit('');
            }
        } elseif (class_exists($class) == false || class_exists($namespace) == false) {
            $output = 'The site address '.$class.' requested does not exist.'. $action ;
            $variables['contentTitle'] = 'ERROR : ' . $cck->_path_segment(1);
            $variables['content'] = $output;
            print $cck->_view('page_404', $variables);
            exit('');
        } else {
            //================= Aliased Menu Url Search =======================//

            $alias = $_SERVER['QUERY_STRING'];


            foreach ($menu as $module) {
                foreach ($module['links'] as $link) {
                    if (array_key_exists('alias', $link)) {
                        if ($link['alias'] === $alias) {


                            $controller = $link['controller'];
                            $action = $link['action'];
                            $cck->_bootstrap($controller, $action);
                            exit('');
                            break;
                        }

                    }
                }
            }
            //===========================================//

            if (method_exists($controller, $action)) {
                return $controller->$action($arguments);
            } elseif (method_exists($namespace, $action)) {
                return $controller->$action($arguments);
            } else {
                $variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
                $output = 'The URL requested ('.$namespace. '/' . $controller . '/' . $action .') does not exist. error:103';
                $variables['content'] = $output;
                print $cck->_view('page_404', $variables);
                exit('');
            }
        }
    }

    public function _model($model = '', $mode = null)
    {
        //
        $model_path = DOCROOT . '/_models' . '/' . $model . '.model.inc';
        if (include_once($model_path)) {
            //
            $data = new $model();
            if (method_exists($data, $mode)) {
                return $data->$mode();
            } else {
                return 'The model was not was not processed.';
            }
        } else {
            return 'The model file was not found.';
        }
    }
    public function session_start()
    { /* Starts the session */


        global $cck,$ini_settings, $_SESSION;

        /* Check Login form submitted */
        if (isset($_POST['login_send'])) {
            /* Define username and associated password array */
            $logins = array(
                'carl@dev.com' => '123456',
                'username1' => 'password1',
                'username2' => 'password2'
            );

            /* Check and assign submitted Username and Password to new variable */
            $Username = isset($_POST['Username']) ? $_POST['Username'] : '';
            $Password = isset($_POST['Password']) ? $_POST['Password'] : '';

            /* Check Username and Password existence in defined array */
            if (isset($logins[$Username]) && $logins[$Username] == $Password) {
                /* Success: Set session variables and redirect to Protected page  */
                $_SESSION['UserData']['Username'] = $logins[$Username];
                header('"location:'.$ini_settings['site']['frontpage'].'"');
                exit;
            } else {
                /*Unsuccessful attempt: Set error message */
                $msg = "<span style='color:red'>Invalid Login Details</span>";
            }
        }
    }

    public function _view($view, $variables, $template = true, $output = null)
    {
        global $cck,$ini_settings;

        // add in some globally used template variables
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');


        $template_path = DOCROOT . '/_views' . '/' . $view . '.tpl.php';

        if (file_exists($template_path) == false) {
            trigger_error("Template {$view} not found in ". $template_path);
            return false;
        }

        // check for empty content and give  default content from template default_content.tpl.php
        if (!isset($variables['content']) || empty($variables['content'])) {
            $variables['content'] = file_get_contents('_views/default_content.tpl.php');


        }

        if (is_array($variables)) {
            // Load variables here because they become part of the module not the theme template.php file.

            $variables['pageTitle'] = (isset($variables['pageTitle']) ? $variables['pageTitle'] : 'empty in template call');
            $variables['contentTitle'] = (isset($variables['contentTitle']) ? $variables['contentTitle'] : 'empty in template call');
            $variables['dbTable'] = (isset($variables['dbTable']) ? $variables['dbTable'] : 'empty in template call');
            $variables['pageUrl'] = (isset($variables['pageUrl']) ? $variables['pageUrl'] : 'empty in template call');
            $variables['postActionUrl'] = (isset($variables['postActionUrl']) ? $variables['postActionUrl'] : 'empty in template call');
            $variables['templateName'] = $view;
            $variables['templatePath'] = $template_path;
            $variables['userName'] = (isset($variables['userName']) ? $variables['userName'] : '');
            $variables['userID'] = (isset($variables['userID']) ? $variables['userID'] : 'shared');
            $variables['profileImage'] = (isset($variables['profileImage']) ? $variables['profileImage'] : 'default_user.jpeg');
            $variables['userBio'] = (isset($variables['userBio']) ? $variables['userBio'] : file_get_contents('_views/default_content.tpl.php'));
            $variables['dbTable'] = (isset($variables['dbTable']) ? $variables['dbTable'] : 'empty dtabase  table variable');
            $variables['userAccess'] = array('userId' => '','groupId' => '', 'permissionList' => '');
            $variables['moduleAccess'] = array('userId' => '','groupId' => '', 'permissionList' => '');
            $variables['urlAccess'] = array('userId' => '','groupId' => '', 'permissionList' => '');
            $variables['installDir'] = $ini_settings['paths']['install_dir'];
            $variables['imagesDir'] = $ini_settings['paths']['images_dir'];
            $variables['cssDir'] = $ini_settings['paths']['css_dir'];
            $variables['jsDir'] = $ini_settings['paths']['js_dir'];
            $variables['jsCDN'] = $ini_settings['paths']['js_cdn'];
            $variables['devSymlink'] = $ini_settings['paths']['dev_symlink'];
            $variables['frontPage'] = $ini_settings['url']['frontpage'];
            $variables['siteName'] = $ini_settings['site']['site_name'];
            $variables['urlSection'] = $cck->_path_segment(0);
            //$variables['elementId'] = (isset($variables['elementId']) !== '' ? $variables['elementId']: 'none-found-in-code');
            //$variables['elementName'] = (isset($variables['elementName']) !== '' ? $variables['elementName']:'none-found-code');

            /* load in the CCK object as a tempalate variable */
            $variables['cck'] = $cck;

            /* ============ call for template content ===========*/
            $output .= $cck->_template($template_path, $variables);

            //$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);

            //var_dump($variables); exit;
        }
        return $output;
    }

    public function _default_content($view, $file)
    {
        switch ($view) {
            case 'archive': $view = 'archive/temp';
                break;
            case 'single': $view = 'single';
                break;
        }

        return $view;
    }

    public function _template($template_file, $variables)
    {
        //
        $template_path = DOCROOT . '/_views' . '/' . $template_file . '.tpl.php';

        ob_start();
        extract($variables, EXTR_SKIP); // Extract the variables to a local namespace
        include $template_file; // Include the template file
        return ob_get_clean(); // End buffering and return its contents
    }

    public function _page_header()
    {
        //
    }

    public function _path_segment($index = null)
    {
        //
        global $cck,$ini_settings;

        $path = $_SERVER['QUERY_STRING'];
        if ($path == '') {
            return;
        } else {
            $parts[$path] = explode('/', $_SERVER['QUERY_STRING']);
        }

        $parameters = $cck->_url_query();

        foreach ($parts[$path] as $key => $segment) {
            $cleaned = explode('&', $segment);
            $parts[$path][$key] = $cleaned[0];
        }

        if (count($parts[$path]) >= 4) {
            $new_path = strtolower($parts[$path][1]) .'_' . strtolower($parts[$path][0]) . '/' . $parts[$path][2];
            $parts[$new_path] = explode('/', $new_path);
            foreach ($parts[$new_path] as $key => $segment) {
                $cleaned = explode('&', $segment);
                $parts[$new_path][$key] = $cleaned[0];
            }
            return $parts[$new_path][$index];
        }

        if (isset($parts[$path][$index])) {
            return $parts[$path][$index];
        }
    }

    public function _t()
    {
        //
    }

    public function _url_alias($alias = null, $menu = array())
    {
        //
        global $cck;
        $alias = $_SERVER['QUERY_STRING'];

        foreach ($menu as $module) {
            foreach ($module['links'] as $link) {
                if (array_key_exists('alias', $link)) {
                    if ($link['alias'] === $alias) {


                        $controller = $link['controller'];
                        $action = $link['action'];
                        $cck->_bootstrap($controller, $action);
                        exit('');
                        break;
                    }

                }
            }
        }
    }
    public function _query_segment()
    {
        $path = $_SERVER['QUERY_STRING'];
        $query[$path] = explode('/', $path);
        $get_last = array_reverse($query[$path]);
        $queryParts = explode('&', $get_last[0]);
        $params = array();


        foreach ($queryParts as $param) {
            $pos = strpos($param, '=');

            // Note our use of ===.  Simply == would not work as expected
            // because the position of 'a' was the 0th (first) character.
            if ($pos === false) {
                //
            } else {
                $item = explode('=', $param);
                $params[$item[0]] = $item[1];
            }

        }

        if (!empty($parameter) && isset($parameter)) {
            return $params[$parameter];
        } else {
            return $params;
        }
    }

    public function _add_css($file)
    {
        global $cck, $ini_settings;
        $css = $ini_settings[path] .'/'. $file;
        if (file_exists($css)) {
            $css = file_get_contents($file);
        }
        print $css;
    }

    public function _add_js($file)
    {
        //
        global $cck, $ini_settings;
        $js = $ini_settings[path] .'/'. $file;
        if (file_exists($js)) {
            $js = file_get_contents($file);
        }
        print $css;
    }

    public function _dbconnect($databaseName = '')
    {
        global $cck, $ini_settings;

        //$database = $ini_settings['databases'][$databaseName];


        $db = new SQLite3($databaseName);
        return $db;


    }

    public function _hooks($hook = null, $type = null)
    {

        global $cck, $ini_settings;
        $output = array();
        $Class = $cck->_path_segment(0) . '\\'. $cck->_path_segment(0) ;

        foreach ($this->_modules_list as $module) {
            try {

                // URI items after the /controller/action are loaded into the function as parameters

                $arguments = implode(',', func_get_args());


                if ($type != null) {
                    //$module = explode('/', $module);
                    $namespace = $module . '_' . $type;
                } elseif (!empty($module)) {
                    $namespace = $module.'\\'.$module;
                } elseif ($Class == null) {

                    $Class = $cck->_path_segment(0) . '\\'. $cck->_path_segment(0) ;

                }

                if (class_exists($module) == true) {
                    $Class = new ReflectionClass($module);
                } elseif (class_exists($namespace) == true) {
                    $Class = new ReflectionClass($namespace);
                }

                if ($Class->hasMethod($hook)) {
                    $Method = new ReflectionMethod($Class->getName(), $hook);
                    if ($Method->isStatic()) {
                        continue;
                    } else {
                        $Instance = $Class->newInstance();
                        $item[$module] = $Method->invoke($Instance);
                        $output = array_merge($output, $item);
                    }
                } else {
                    continue;
                }

            } catch (Exception $e) {
                continue;
            }

        }

        return $output;
    }

    public function _allhooks()
    {
        //
    }

    public function _varset()
    {
        //
    }

    public function _target($operation, $item = null)
    {

        //var_dump($_POST); exit;
        global $cck, $ini_settings;
        $output = '';

        switch ($operation) {

            case 'is_front':

                $frontPage = $ini_settings['url']['frontpage'];
                if ($frontPage == $_SERVER['QUERY_STRING']) {

                    /* prevent query string parameters (&'s) from interfering with the string comparison */
                    if ($cck->_url_query(0) == 0) {
                        $output = true;
                    }

                } else {

                    $output = false;
                }

                break;
            case 'form_post':

                foreach ($_POST as $name => $text) {

                    $output .= $name.  ' ===> ' . $text. "\n<br>";
                }
                break;
            case 'form_post_json':

                //$json_string = json_encode($_POST , JSON_PRETTY_PRINT);

                // $output .= $json_string . "\n<br>";

                break;
            case 'var_dump':
                $output = $cck->_view('table_var_dump', $variables);
                //$json_string = json_encode($_POST , JSON_PRETTY_PRINT);

                // $output .= $json_string . "\n<br>";

                break;

            case 'array2text':
                function array2text($array)
                {
                    $output = '';
                    $counter = 0;
                    foreach ($item as $name => $text) {

                        $output .= $name .  ' ===> ' . $text. "\n<br>";
                        if (is_array($text) && $counter < 3) {

                            array2text($text);
                        }
                    }
                }
                break;

        }
        return $output;


    }

    public function _vardel()
    {
        //
    }
    public function _requireToVar($file)
    {
        ob_start();
        require($file);
        return ob_get_clean();
    }

    public function _link($template = null, $variables = array())
    {
        global $cck,$ini_settings;

        $variables['elementId'] = 'no_id_found_link_variables';
        $variables['elementName'] = 'no_id_found_link_variables';

        $output =  $this->_view($template, $variables);
        return $output;
    }

    public function _menu_links($menu, $template = null, $variables, $style = null, $index = null)
    {
        //
        global $cck,$ini_settings;
        $list = array();

        foreach ($menu as $section => $group) {
            //print $section;
            $counter = 1 ;
            foreach ($group['links'] as $key => $value) {




                if ($template == 'links_main_menu') {
                    $variables['elementId'] = (isset($value['css_id']) != "" ? '_'. $value['css_id'] : $counter);
                    $variables['elementName'] = (isset($value['css_class']) != "" ? implode('_', $value['css_class']) : $counter);
                    $value['elementName'] = (isset($value['css_class']) != "" ? implode('_', $value['css_class']) : '_'.$counter);
                    $value['elementId'] = (isset($value['css_id']) != "" ? $counter.'-'.$value['css_id'] : '-'.$counter);
                    $value['enumerate'] = $counter;
                    $list[$section][] = $this->_view('links_main_anchors', $value);
                    //var_dump($value);
                } else {



                    $variables['elementName'] = (isset($value['css_class']) != "" ? implode('_', $value['css_class']) : '_'. $counter);
                    $variables['elementId'] = (isset($value['css_id']) != "" ? $counter.'-'.$value['css_id'] : '-'. $counter);
                    $value['enumerate'] = $counter;
                    $list[$section][] = $this->_view('links', $value);

                    //var_dump($value);
                }


                $counter = $counter + 1;
            }
            //var_dump($value);
        }
        //exit(var_dump( $value) .var_dump($list));
        $variables['menu_index'] = $index;
        $variables['links'] = $list;
        $variables['separator'] = '-';
        //var_dump( $value);
        //echo '==========================>';
        //var_dump($variables);
        //exit;
        $output =  $this->_view($template, $variables);

        return $output;
    }

    /**
     *  typically links here are created as sub navigation dropdowns
     */
    public function _module_links($menu, $attributes = array(), $variables)
    {

        global $cck,$ini_settings;
        $list = array();
        //var_dump($variables);
        //exit(var_dump($attributes));
        //exit;

        if (isset($menu)) {
            $counter = 1;
            foreach ($menu['links'] as $key => $link) {
                //print '<pre>' . print_r($links, 1) . '</pre>';
                $link['elementId'] = (isset($attributes['css_id']) !== '' ? '-' . $attributes['css_id'] : '-' . $counter);
                $link['elementName'] = (isset($attributes['css_class'])  && !empty($attributes['css_class']) ? implode('_', $attributes['css_class']) : '_'. $counter);
                $link['enumerate'] = $counter;
                $variables['elementId'] = (isset($attributes['css_id']) !== '' ? '-' . $attributes['css_id'] : '-' . $counter);
                $variables['elementName'] = (isset($attributes['css_class'])  && !empty($attributes['css_class']) ? implode('_', $attributes['css_class']) : '_'. $counter);
                $variables['enumerate'] = $counter;
                $list[] = $this->_view('links', $link);

                $counter = $counter + 1;

            }

        }

        $variables['menu_index'] = $attributes['index'];
        $variables['links'] = $list;

        $output =  $this->_view($attributes['template'], $variables);

        return $output;
    }

    public function _url_query($parameter = null)
    {
        $queryParts = array();
        $path = $_SERVER['QUERY_STRING'];
        $query[$path] = explode('/', $path);
        $get_last = array_reverse($query[$path]);
        $queryParts = explode('&', $get_last[0]);
        $params = array();

        foreach ($queryParts as $param) {
            $item = explode('=', $param);
            if (isset($item[1])) {
                $params[$item[0]] = $item[1];
            } else {
                continue;
            }
        }
        if (!empty($params) && array_key_exists($parameter, $params)) {
            return $params[$parameter];
        } else {
            return ;
        }
    }


}

/**
*
* @author Carl McDade
* @since 2024.11.9
*
* These methods cannot be called directly by MODULES they are outside the scope
* of the CCK class. But global to this file.
*
*/
/**
* ini file methods
* _______________________
*   cck_array_2_ini
*   cck_ini_2_array
*   cck_save_ini_file
* _______________________
* process
* _______________________
*   read from ini file to array
*   make changes to array values
*   write array to ini file
*
*/

function cck_ini_2_array($ini_array)
{


}

function cck_array_2_ini($ini_array, $out = "")
{

    $t = "";
    $q = false;
    foreach ($ini_array as $c => $d) {
        if (is_array($d)) {
            $t .= array_to_ini($d, $c);
        } else {
            if ($c === intval($c)) {
                if (!empty($out)) {
                    $t .= "\r\n".$out." = \"".$d."\"";
                    if ($q != 2) {
                        $q = true;
                    }
                } else {
                    $t .= "\r\n".$d;
                }
            } else {
                $t .= "\r\n".$c." = \"".$d."\"";
                $q = 2;

            }

        }

    }

    if ($q != true && !empty($out)) {
        return "[".$out."]\r\n".$t;
    }
    if (!empty($out)) {
        return  $t;
    }
    return trim($t);

}


function cck_save_ini_file($ini_array, $file)
{
    global $cck,$ini_settings;
    $buffer = $cck->_array_2_ini($ini_array);
    $handel = fopen($file, "w");
    fwrite($handle, $buffer);
    fclose($handle);
}


function cck_get_class_comments($fullyQualifiedClassName)
{

    global $ck, $ini_settings;
    $refClass = new ReflectionClass($fullyQualifiedClassName);
    $comments = array();

    foreach ($refClass->getProperties() as &$refProperty) {
        $comments[$refProperty->getName()]  =  trim(preg_replace("#((\/)?(\*{1,2})(\/)?)#si", "", $refProperty->getDocComment()));
    }
    return $comments;
}



function cck_render_template($template_file, $variables)
{
    ob_start();
    extract($variables, EXTR_SKIP); // Extract the variables to a local namespace
    include $template_file; // Include the template file
    return ob_get_clean(); // End buffering and return its contents
}


function cck_t($string)
{
    return $string;
}

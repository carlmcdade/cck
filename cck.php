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
define('INSTALLDIR',basename(__DIR__));
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
    public  $common;
    public  $default_main_menu = 'links_main_menu';
    public  $default_admin_menu = 'links_admin_menu';
    public  $_modules_list;
    public  $hooks_list;
    public  $moduleName;
    public  $section;
    public  $dbc;
    public  $type = 'common';
	
	
	function __construct()
	{
		//
		spl_autoload_register(array($this, '_autoload'));
		spl_autoload_register(array($this, '_helpers_autoload'));
		spl_autoload_register(array($this, '_frameworks_autoload'));
		
		if(file_exists( INI_FILENAME ))
        {
            
            $this->ini_settings =  parse_ini_file(INI_FILENAME, TRUE);
            $this->_modules_list = $this->ini_settings['modules'];
            $this->hooks_list = $this->ini_settings['hooks'];
            
            
        }
		
	}
	
	function __tostring()
	{
		//
        return 'cck';
	}
	
	function _autoload($class)
	{
		//
		global $ini_settings;
		static $common_loaded = FALSE;
		
		//CCK
		
		
		// directories
		$controllers = $ini_settings['system']['controllers'];
		$helpers = $ini_settings['system']['helpers'];
		
		// load the common controller items first
		if($common_loaded == FALSE)
		{
			
			//CCK loader
			$path = DOCROOT . '/cck.php';	
			if(file_exists($path))
			{
				require_once($path);
			}			
			
			foreach($ini_settings['common'] as $suffix)
			{
				//$class = strtolower(ber_pathpart(0));
				$path = DOCROOT . '/_controllers/common/' . 'common' . '_' . $suffix . '.class.inc';	
				if(file_exists($path))
				{
					require_once($path);
					
				}						
			}
			
			$common_loaded = TRUE;
		}
		
		// get a list of class file names. Allow only these and not Drupal class files in array
		$class = strtolower($class);
		$check_class = substr_count($class, '_');
		
		// load the modules standard controller
		if($check_class == 0)
		{
		
			// try and load without namespace 
			$path = DOCROOT . '/_controllers/'. $class . '/' . $class . '.class.inc';
			
			if(file_exists($path))
			{
				require_once($path);
			}
			
			spl_autoload_register(
				function($class)
				{
					$parts = explode('\\', $class);
				
					# Support for non-namespaced classes.
					$parts[] = str_replace('_', DIRECTORY_SEPARATOR, array_pop($parts));
				
					$path = implode(DIRECTORY_SEPARATOR, $parts);
				
					$file = stream_resolve_include_path($path.'.class.inc');
					if($file !== false) {
						require $file;
					}
				}
			);

			
			$modules_loaded = TRUE;
		}
		// load modules helper controllers and  sub classes
		elseif($check_class > 0)
		{			
			$list = preg_split('/_/', $class);
			$controller = $list[0];
			$hook = $list[1];
			// get the types of class files that belong to a controller module from the ini settings file
			// do a loop here to compare the values of the ini and the suffix
			$path = '';
			foreach($ini_settings['suffixes'] as $suffix)
			{			
				if($hook == $suffix && $controller != 'common')
				{	
					//$class = strtolower(ber_pathpart(0));
					$path = DOCROOT . '/_controllers/'. $controller . '/' . $controller . '_' . $suffix . '.class.inc';		
					if(file_exists($path))
					{
						require_once($path);						
					}						
				}
			}	
			$sub_modules_loaded = TRUE;
			$modules_loaded = FALSE;
			$debug = '';			
		}
		
		// load module controllers that have a set namespace
		else
		{
			return;
		}
	}
	
	function _helpers_autoload($class)
	{
		//
		$class = strtolower($class);
		$path = DOCROOT . '/_helpers/' . $class . '/' . $class . '.php';
		$path = str_replace("\\", "/", $path);
		
		if(file_exists($path))
		{
			require_once($path);
		}
		return;
	}
	
	function _frameworks_autoload($class)
	{
		//
		
	}
	
	function _bootstrap($inclass = NULL, $foraction = NULL)
	{
		// required
		global $cck,$ini_settings;
		$controller = NULL;
		$action = NULL;
		$arguments = implode(',', func_get_args());
		$variables = $ini_settings['modules'];
			
		// $allow alias to load [controller]/[action] directly using bootstrap to avoid HTTP redirects
		if($inclass && $foraction)
		{
			$class = $inclass;
			$action = $foraction;
			
		}
		else
		{
			$class = strtolower($cck->_path_segment(0));
			$action = strtolower($cck->_path_segment(1));
		}		
		
		$menu = $cck->_hooks('hook_links');
		$access = $cck->_hooks('hook_access');
		
		$namespace = $class.'\\'.$class;
		$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
		
		if(class_exists($class) == TRUE || class_exists($namespace) == TRUE)
		{
			// if not in a namespace then go to root class
			if(class_exists($class) == TRUE)
			{
				$controller = new $class();
				if(method_exists($controller, $action))
				{
					return $controller->$action($arguments); // send string of arguments
				}
				else
				{
					$class = str_replace('_','/',$class);				
					$output = 'The address requested '. $class .'/'. $action.' does not exist. 1001' ;
					$variables['contentTitle'] = 'ERROR : ' . $cck->_path_segment(1);
					$variables['content'] = $output;
					print $cck->_view('page_404', $variables);
					exit('');
				}
			}			
			elseif(class_exists($namespace) == TRUE)
			{
				$controller = new $namespace();
				if(method_exists($controller, $action))
				{
					return $controller->$action($arguments); // send string of arguments
				}				
				else
				{
					$output = 'The address requested '. $class .'/'. $action.' does not exist.';
					$variables['contentTitle'] = 'ERROR : ' . $cck->_path_segment(1);
					$variables['content'] = $output;
					print $cck->_view('page_404', $variables);
					exit('');
				}
			}
			else
			{
				$output = 'The site address requested does not exist.'. $action ;
				$variables['contentTitle'] = 'ERROR : ' . $cck->_path_segment(1);
				$variables['content'] = $output;
				print $cck->_view('page_404', $variables);
				exit('');
			}
		}elseif(class_exists($class) == FALSE || class_exists($namespace) == FALSE){
		       	$output = 'The site address '.$class.' requested does not exist.'. $action ;
				$variables['contentTitle'] = 'ERROR : ' . $cck->_path_segment(1);
				$variables['content'] = $output;
				print $cck->_view('page_404', $variables);
				exit(''); 
		}
		else
		{
			//================= Aliased Menu Url Search =======================//
			
			$alias = $_SERVER['QUERY_STRING'];
			
			
			foreach($menu as $module)
			{
				foreach($module['links'] as $link)
				{
					if(array_key_exists('alias', $link))
					{
						if($link['alias'] === $alias)
						{
							
							
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
			
			if(method_exists($controller, $action))
			{
				return $controller->$action($arguments);
			}
			elseif(method_exists($namespace, $action))
			{
				return $controller->$action($arguments);
			}
			else
			{
				$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu',$variables);
				$output = 'The URL requested ('.$namespace. '/' . $controller . '/' . $action .') does not exist. error:103';
				$variables['content'] = $output;
				print $cck->_view('page_404', $variables);
				exit('');
			}
		}
	}
	
	function _model($model = '', $mode = NULL)
	{
		//
		$model_path = DOCROOT . '/_models' . '/' . $model . '.model.inc';
		if(include_once($model_path))
		{
			//
			$data = new $model;
			if(method_exists($data,$mode))
			{
				return $data->$mode();
			}
			else
			{
				return 'The model was not was not processed.';
			}
		}
		else
		{
			return 'The model file was not found.';
		}
	}
	
	function _view($view, $variables, $template = true, $output = NULL)
	{
		global $cck,$ini_settings;
		
		// add in some globally used template variables
		$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	
	
		$template_path = DOCROOT . '/_views' . '/' . $view . '.tpl.php';
    
    	if (file_exists($template_path) == false)
    	{
    		trigger_error("Template {$view} not found in ". $template_path);
    		return false;
    	}	
    	
    	// check for empty content and give  default content from template default_content.tpl.php
    	if(!isset($variables['content']) || empty($variables['content']))
    		{
    		    		$variables['content'] = file_get_contents('_views/default_content.tpl.php');

    		
    		}
    
    	if(is_array($variables))
    	{
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
    	    $variablea['siteName']= $ini_settings['site']['site_name'];
    	    $variables['urlSection']= $cck->_path_segment(0);
    	    
     	    
     	    
    	    
    	    $output .= $cck->_template($template_path, $variables);
    	    //$variables['mainNavigation'] = $cck->_menu_links($menu, 'links_main_menu', $variables);
    	    
    		//var_dump($variables); exit;
    	}   
    	return $output;
	}
	
	function _default_content( $view, $file )
    {
        switch ( $view )
    {
           case 'archive': $view = 'archive/temp'; break;
           case 'single' : $view = 'single';       break;
    }

           return $view;
    }
	
	function _template($template_file, $variables)
	{
		//
		$template_path = DOCROOT . '/_views' . '/' . $template_file . '.tpl.php';

		ob_start();
		extract($variables, EXTR_SKIP); // Extract the variables to a local namespace
		include $template_file; // Include the template file
		return ob_get_clean(); // End buffering and return its contents
	}
	
	function _page_header()
	{
		//
	}
	
	function _path_segment($index = NULL)
	{
		//	
		$path = $_SERVER['QUERY_STRING'];
		if($path == '')
		{
			return;
		}
		else
		{
			$parts[$path] = explode('/', $_SERVER['QUERY_STRING']);
		}
		
		$parameters = cck_url_query();
	
		foreach($parts[$path] as $key => $segment)
		{
			$cleaned = explode('&', $segment);
			$parts[$path][$key] = $cleaned[0];
		}
		
		if(count($parts[$path]) >= 4)
		{
			$new_path = strtolower($parts[$path][1]) .'_' . strtolower($parts[$path][0]) . '/' . $parts[$path][2];
			$parts[$new_path] = explode('/', $new_path);		
			foreach($parts[$new_path] as $key => $segment)
			{
				$cleaned = explode('&', $segment);
				$parts[$new_path][$key] = $cleaned[0];
			}			
			return $parts[$new_path][$index];
		}
		
		if(isset($parts[$path][$index]))
		{
			return $parts[$path][$index];
		}
	}
	
	function _translate()
	{
		//
	}
	
	function _url_alias($alias = NULL, $menu = array())
	{
		//
        global $cck;
		$alias = $_SERVER['QUERY_STRING'];
					
			foreach($menu as $module)
			{
				foreach($module['links'] as $link)
				{
					if(array_key_exists('alias', $link))
					{
						if($link['alias'] === $alias)
						{
							
							
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
	function _query_segment()
	{
			$path = $_SERVER['QUERY_STRING'];
			$query[$path] = explode('/', $path);
			$get_last = array_reverse($query[$path]);
			$queryParts = explode('&', $get_last[0]);
			$params = array();
		
		    
			foreach ($queryParts as $param)
			{				
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
			
			if(!empty($parameter) && isset($parameter))
			{
				return $params[$parameter];
			}
			else
			{
				return $params;
			}
	}
	
	function _add_css()
	{
		//
	}
	
	function _add_js()
	{
		//
	}
	
	function _dbconnect($databaseName = '')
	{
		global $cck, $ini_settings;
		
		//$database = $ini_settings['databases'][$databaseName];
				 

            $db = new SQLite3($databaseName);
            return $db;
	
			
	}
	
	function _hooks($hook = NULL, $type = NULL)
	{		
		
		global $cck, $ini_settings;
		$output = array();
		
		foreach ($this->_modules_list as $module)
		{                   		    	       
		    try
		    {
		
				// URI items after the /controller/action are loaded into the function as parameters
										
				$arguments = implode(',', func_get_args());
				
				
				if($type != NULL)
	            {
	            	//$module = explode('/', $module);	            	
	            	$namespace = $module . '_' . $type;	            	            	
	            }
	            
	            elseif(!empty($module))
	            {
		            $namespace = $module.'\\'.$module;
	            }
	            /**
	            elseif(empty($module)){
	            
	            	$namespace = $cck->_path_segment(0) . '\\'. $cck->_path_segment(0) ;
	                
	            }*/
							
					if(class_exists($module) == TRUE)
					{
						$Class = new ReflectionClass($module);
					}			
					elseif(class_exists($namespace) == TRUE)
					{						
						$Class = new ReflectionClass($namespace);	
					}
					
					if($Class->hasMethod($hook))
					{
						$Method = new ReflectionMethod($Class->getName(), $hook);
						if ($Method->isStatic())
						{
							continue;
						}
						else
						{							
							$Instance = $Class->newInstance();
							$item[$module] = $Method->invoke($Instance);
							$output = array_merge($output, $item);					
						}															
					}
					else
					{
						continue;
					}
					
		    }
		    catch(Exception $e)
		    {
		    	continue;
		    }     
		    
		}
		
		return $output;
	}
	
	function _allhooks()
	{
		//
	}
	
	function _varset()
	{
		//
	}
	
	function _target($operation)
	{
		
		//var_dump($_POST); exit;
		global $cck, $ini_settings;
		$output='';
		
		switch($operation){
		
		case 'is_front' :
			
			$frontPage = $ini_settings['frontpage'];
            if($frontPage == $_SERVER['QUERY_STRING']){
        	
        	    $output = TRUE;
        	
            }else{
        
               $output = FALSE; 
            }
			
		break;
		case 'form_post' :
        
             foreach($_POST as $name => $text){
             
			     $output .= $name.  ' ===> ' . $text. "\n<br>";
			 }
			break;
		default:
			$output = 'say what???';
			
			
		}
	 return $output;
		
		
	}
	
	function _vardel()
	{
		//
	}
	function _requireToVar($file){
        ob_start();
        require($file);
        return ob_get_clean();
    }
	
	function _link($template = NULL, $variables = array())
	{
		//
		$output =  $this->_view($template, $variables);
		return $output;
	}
	
	function _menu_links($menu, $template = NULL, $variables, $separator = NULL, $index = NULL)
	{
		//
		global $cck,$ini_settings;
		$list= array();
		
    	foreach($menu as $section => $group)
    	{	
    		//print $section;
    		foreach($group['links'] as $key => $value)
			{				
				$list[$section][] = $this->_view('links', $value);	
				
			}
			
    	}
    	$variables['menu_index'] = $index;
    	$variables['links'] = $list;
        $variables['separator'] = $separator;
    	
    	$output =  $this->_view($template, $variables);
    	
    	return $output;
	}
	
	function _module_links($menu, $attributes = array(), $variables)
	{
		
		global $cck,$ini_settings;
		$list = array();
		//var_dump($variables);
		//var_dump($attributes);
		//exit;
    	if(isset($menu)){ 	 
    	  foreach($menu['links'] as $link)
    	  {
    		//print '<pre>' . print_r($links, 1) . '</pre>';
    		$list[] = $this->_view('links', $link);		
    	    }
    	}
    	
    	$variables['menu_index'] = $attributes['index'];
    	$variables['links'] = $list;
    	 
    	$output =  $this->_view($attributes['template'], $variables);
    	 
    	return $output;
	}

}

/** 
*
@author Carl McDade
@since 2024.11.9

These methods cannot be called directly by MODULES they are outside the scope
of the CCK class. But global to this file.

*/

function cck_access()
{
	echo 'this is a cck non global function';
	exit;

}



/**
* ==================================== MODEL ===================================
* @author Carl McDade
* @since 2012-07-14
* Start the class loader function. The arguments are the Class name
*
* Add any database routines here and load the results into variables. Complicated
* solutions should be placed in a model file
*
* Add any business logic here and load the results to variables. Complicated
* solutions should be placed in a model file
*
*/


function cck_model( $model, $mode = NULL, $parameter = NULL )
{
	$model_path = DOCROOT . '/_models' . '/' . $model . '.model.inc';
	if(include_once($model_path))
	{
		//
		$data = new $model;
		if(method_exists($data,$mode))
		{
			return $data->$mode();
		}
		else
		{
			return 'The model was not was not processed.';
		}
	}
	else
	{
		return 'The model file was not found.';
	}
}

/**
* @todo Update INI file methods to handle sections and add these to INI file
*
* the array of permission actually have to exists in the hook_perm fuction used by Drupal
* the reason I do this here is to enforce the ordered mvc routing conventions 
* over the chaotic Drupal ones. MVC usage hints to where and what is being used in the code
* while Drupal allows anything to hide anywhere.
*
*/
	


function cck_render_template($template_file, $variables)
{
    ob_start();
	extract($variables, EXTR_SKIP); // Extract the variables to a local namespace
	include $template_file; // Include the template file
	return ob_get_clean(); // End buffering and return its contents
}


/**
* A module-defined block content function.
*/

function cck_pathpart($index = NULL)
{
	
	$path = $_SERVER['QUERY_STRING'];
		
	
	if($path == '')
	{
		return;
	}
	else
	{
		$parts[$path] = explode('/', $_SERVER['QUERY_STRING']);
	}
	
	$parameters = ber_url_query();

	foreach($parts[$path] as $key => $segment)
	{
		$cleaned = explode('&', $segment);
		$parts[$path][$key] = $cleaned[0];
	}
		
	//	
	
	if(count($parts[$path]) >= 3 && $parts[$path][2])
	{
		$class = strtolower($parts[$path][1]) .'_' . strtolower($parts[$path][0]);
		$namespace = $class . '//' . $class;
		
		if(class_exists($class) == TRUE || class_exists($namespace) == TRUE)
		{
			$new_path = strtolower($parts[$path][1]) .'_' . strtolower($parts[$path][0]) . '/' . $parts[$path][2];
			$parts[$new_path] = explode('/', $new_path);
			
			foreach($parts[$new_path] as $key => $segment)
			{
				$cleaned = explode('&', $segment);
				$parts[$new_path][$key] = $cleaned[0];
			}
			
			return $parts[$new_path][$index];
	    }
	}
	
	if(isset($parts[$path][$index]))
	{
		return $parts[$path][$index];
	}
}

function cck_translatable($string)
{
	//
	return $string;
}

function cck_uri($path = NULL)
{
	//
	return $path;
}

/**
 * Returns the url query as associative array
 *
 * @param    string    query
 * @return    array    params
 */
 
function cck_url_query($parameter = NULL)
{
	$queryParts = array();
	$path = $_SERVER['QUERY_STRING'];
	$query[$path] = explode('/', $path);
	$get_last = array_reverse($query[$path]);
	$queryParts = explode('&', $get_last[0]);
	$params = array();
	
	foreach ($queryParts as $param)
	{
		$item = explode('=', $param);
		if(isset($item[1]))
		{
			$params[$item[0]] = $item[1];
		}
		else
		{
			continue;
		}
	}
	if(!empty($params) && array_key_exists($parameter, $params))
    {
    	return $params[$parameter];
    }
    else
    {
    	return ;
    }
} 



?>
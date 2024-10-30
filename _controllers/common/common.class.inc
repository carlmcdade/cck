<?php

/**
 * @author Carl McDade 
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT
 * 
 * @link http://berlinto.com
 * ==================================================================
 * 
 *                        common.class.inc
 * 
 * ==================================================================
 *
 * @TODO make a template for this comment
 * 
 */



class common{

    static private $_instance;
    private $data = array();
    private $ini_settings = array();
    private $update = FALSE;
    public  $common;
    public  $default_main_menu = "links_main_menu";
    public  $default_admin_menu = "links_admin_menu";
    public  $modules_list;
    public  $hooks_list;
    public  $moduleName;
    public  $section;
    public  $dbc;
    public  $type = "common";

    /**
     * @todo create a registry for modules and hooks
    */
    
    
    private function __construct()
    {

    	$this->moduleName = get_class($this);  
    	//Please extend this class to gain extra functionality

        if(file_exists( INI_FILENAME ))
        {
            /*
             * suppress the warning that comes with using serialized data
             * parse_ini_file() accepts and sends serialixzed data fine
             *
             * @todo Change this to PHP 5.3.0 a.s.a.p which will accept raw data
             * by setting the parameter
             *
             */
            $this->ini_settings =  parse_ini_file(INI_FILENAME, TRUE);
            $this->modules_list = $this->ini_settings['modules'];
            $this->hooks_list = $this->ini_settings['hooks'];
            
        }

    }

    function __destruct()
    {

    }

    private function __clone()
    {
        throw new Exception('Please extend this Class to gain that functionality');
    }

    final public static function get_instance()
    {
        return isset(self::$_instance) ? self::$_instance : self::$_instance = new self();
    }
	
    function hook_admin_links()
    {
        $link = 'links';      
           	
    	$var[$link][1] = array(
        		'text' => 'Commonstuff', 
        		'path' => '?admin/'.$this->module.'/content_type_list'
        		);
        $var[$link][2] = array(
        		'text' => 'more ', 
        		'path' => '?admin/'.$this->module.'/content_type_add'
        		);

        return $var;
    }
	
    function get_hooks($hook = NULL, $type = NULL)
    {

       
    	$output = array();
        
        // get the hooks for the common controller ex. hook_links separately as they cannot be called
        // directly in a loop

        

        foreach ($this->modules_list as $module)
        {
                       
            // hook may not exist in all modules. Handle exception with 
            // continue
        	
            if($type != NULL)
            {
            	
            	$module = explode('_', $module);
            	$module = $module[0] . '_' . $type;
            	
            }
                      
            try
            {
                $Class = new ReflectionClass($module);
                $Method = new ReflectionMethod($Class->getName(), $hook);
                $Instance = $Class->newInstance();
            }
            catch(Exception $e)
            {
                continue;
            }       

            /*
             * 
             * Static methods do not require a Class instance
             * Invoking a private method is not allowed. 
             * The exception is handled by ignoring the method and continuing on
             * 
             */

            if ($Method->isStatic())
            {
                $Instance = NULL;
            }
                
            try
            {
                
            	$item[$module] = $Method->invoke($Instance);
            	$output = array_merge($output, $item);
            	
            }
            catch(Exception $e)
            {
                trigger_error('You are attempting to use a private method.');
                continue;
            }
             
        }
        
       
        $this->data = $output;
       
        return $this->data;
    }
    

    function get_all_hooks($type = NULL)
    {
        $output = array();

        foreach ($this->hooks_list as $hook)
        {
            $output[$hook] = $this->get_hooks($hook, $type);
        }

        $this->data = $output;
        return $this->data;
    }

    public function var_get($name)
    {
        if(isset($this->ini_settings[$name]))
        {
            $output = unserialize($this->ini_settings[$name]);
            return $output;

        }
        else
        {
            return(NULL);
        }
    }

    public function var_set($name, $value)
    {
       ////update only on change
       if(!isset($this->ini_settings[$name]) || ($this->ini_settings[$name] != $value))
       {
           $this->ini_settings[$name] = serialize($value);
           $this->update = TRUE;
       }
       return;

    }

    /*
     * Sometimes you need or want to delete the variable completely
     *
     */
    function var_delete($name)
    {
        unset($this->ini_settings[$name]);
        $this->delete[] = $name;
        return;
    }
    
    /**
     * ===================================== MODEL ===================================
     * @author Carl McDade
     * @since 2010-02-14
     a template is choosen from the _view directory.Be careful not to use
     * the same template twice ie. both as parent and child template in the ber_view().
     * @TODO fix it so that duplicates cannot happen
     *
     */
     
     
	function ber_model( $model, $mode, $parameter = NULL )
	{	
		$model_path = DOCROOT . '/_models' . '/' . $model . '.model.inc';
		if(include_once($model_path))
		{
			//
			$data = new $model;
			if(method_exists($data,$mode))
			{
				//
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
     * ===================================== VIEW ===================================
     * @author Carl McDade
     * @since 2010-02-14
     a template is choosen from the _view directory.Be careful not to use
     * the same template twice ie. both as parent and child template in the ber_view().
     * @TODO fix it so that duplicates cannot happen
     *
     */
    
    function ber_view($view, $variables = NULL, $template = true, $output = NULL)
    {
    
    	$template_path = DOCROOT . '/_views' . '/' . $view . '.tpl.php';
    
    	if (file_exists($template_path) == false)
    	{
    		trigger_error("Template {$view} not found in ". $template_path);
    		return false;
    	}
    
    	if(is_array($variables))
    	{
    		// Load variables here because they become part of the module not the theme template.php file.
    		$output .= ber_render_template($template_path, $variables);
    	}
    
    
    	//
    	return $output;
    
    }
    
    
    
    
    function ber_links_menu($menu, $template = NULL, $separater = NULL, $index = NULL)
    {
    	
    	$list = array();
    
    	
    	foreach($menu as $section => $group)
    	{	
    		//print $section;
    		foreach($group['links'] as $key => $value)
			{				
				$list[$section][] = $this->ber_view('links', $value);				
			}   		
    	}
    	$variables['menu_index'] = $index;
    	$variables['links'] = $list;
    	
    	$output =  $this->ber_view($template, $variables);
    	
    	return $output;
    	
    }
    
    function ber_module_menu($menu, $attributes = array())
    { 	 
    	$list = array();
    	  	 
    	foreach($menu['links'] as $link)
    	{
    		//print '<pre>' . print_r($links, 1) . '</pre>';
    		$list[] = $this->ber_view('links', $link);		
    	}
    	
    	$variables['menu_index'] = $attributes['index'];
    	$variables['links'] = $list;
    	 
    	$output =  $this->ber_view($attributes['template'], $variables);
    	 
    	return $output;
    	 
    }
    

}

?>

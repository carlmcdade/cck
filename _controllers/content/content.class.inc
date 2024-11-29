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




        $result = $db->query('SELECT id,name,desc FROM content_types');
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
                'path' => $this->module . '/content_types',
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




        $result = $db->query('SELECT id,name,desc FROM content_types');
        while ($row = $result->fetchArray()) {
            $rows[] = $row;
        }

        //var_dump($rows); exit;
        $link = 'links';
        foreach ($rows as $key => $value) {
            $var[$link][$key] = array(
                'text' => $value['name'],
                'path' => $this->module . '/content_add_post/' . $value['id'],
                'css_class' => array($this->module, 'module_item'),
                'css_id' => $this->module . ''
                );
        }

        $var[$link][] = array(
                'text' => 'Create Type',
                'path' => $this->module . '/content_type_create',
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


        $typeID = $cck->_path_segment(2);
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

    public function content_post_save()
    {
        global $cck,$ini_settings;

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
		
        $view_content['content_post'] = $_POST;
		$view_content['content_type'] = $_POST['content_type'];
		$view_content['content_id'] = $_POST['content_id'];
		$view_content['content_time_created'] = $_POST['content_time'];  
		$view_content['content_type_id'] = $_POST['content_type_id'];
		$view_id = $cck->_path_segment(2);


        $output = $this->module;
        $output .= '<pre>'. print_r($view_content, true);
        $output .= '</pre>';

    
		
        $variables['pageTitle'] = $view_id .' Saved';
        $variables['contentTitle'] = $view_id .' Saved';
        $variables['content'] =  $output;
        print $cck->_view('default', $variables);

    }

    public function content_add_post()
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
		$form['contentId'] = $form['contentType'].'-'.hash('crc32',$cck->_path_segment(1).time() . mt_rand()) .'-'. $form['userName'];
        $form['contentTime'] = date("Y-m-d H:i:s"); 
        $output = $cck->_view('form_user_content_post', $form);



        $variables['content'] = 'create new content using <h3><i>'.$form['contentType'].'</i></h3>' . $output;

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
		$form['contentId'] = $form['contentType'].'-'.hash('crc32',$cck->_path_segment(1).time() . mt_rand()) .'-'. $form['userName'];
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

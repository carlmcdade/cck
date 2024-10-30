<?php

// Define a class
class content_forms {
  // Sets properties
  public $user_id;
  public $user_name_first;
  public $user_name_last;
  
  
  function __construct()
  {
  	//Test the Common settings
  	$this->common = Common::get_instance();
  	$this->section = get_class($this);
  
  	// connect to the database
  	$this->dbc = dbconn::connect();
  
  }

  // Method of the class
  function content_forms_add_type_field() {
    // Returns a string with the properties value. Uppercase the first character of each word
    /*
     * <field>
    	<type>textbox</type>
    	<label></label>
    	<name>mytextbox</name>
    	<id>mytextbox-id</id>
    	<class>mytextboxes</class>
    	<autocomplete>no</autocomplete>
    	<disabled>no</disabled>
    	<validate callback="content_validate_length">no</validate>
    	<required>yes</required>
    	<characters>20</characters>
    	<visibility>
    		<label>yes</label>
    		<description>no</description>
    	</visibility>
    	<styles>
    		<font-weight>bold</font-weight>
    		<font-family>Times New Roman</font-family>
    		<color>#777777</color>
    		<border>1px solid #999999</border>
    	</styles>
    	<template>default</template>
    	<datatype>string</datatype>
    	<value>some text values</value>
    </field>
     */
  	$form = new Form("content_forms_add_type_field", 300);
  	 	
  		$form->addElement(new Element_Textbox("Element Type:", "content_field_type", array("value" => "type")));
  		$form->addElement(new Element_Textbox("Label:", "content_field_label", array("value" => "label")));
  		$form->addElement(new Element_Textbox("Name:", "content_field_name", array("value" => "name")));
  		$form->addElement(new Element_Textbox("CSS ID:", "content_field_id", array("value" => "id")));
  		$form->addElement(new Element_Textbox("CSS Class:", "content_field_class", array("value" => "class")));
  		$form->addElement(new Element_Textbox("Autocomplete:", "content_field_autocomplete", array("value" => "autocomplete")));
  		$form->addElement(new Element_Textbox("Disabled:", "content_field_disabled", array("value" => "disabled")));
  		$form->addElement(new Element_Textbox("Validate:", "content_field_validate", array("value" => "validate")));
  		$form->addElement(new Element_Textbox("Required:", "content_field_required", array("value" => "required")));
  		$form->addElement(new Element_Textbox("Number of characters:", "content_field_characters", array("value" => "characters")));
  		$form->addElement(new Element_Textbox("Visibility:", "content_field_visibility", array("value" => "visibility")));
  		$form->addElement(new Element_Textbox("Styles:", "content_field_styles", array("value" => "styles")));
  		$form->addElement(new Element_Textbox("Template:", "content_field_template", array("value" => "template")));
  		$form->addElement(new Element_Textbox("Data type:", "content_field_datatype", array("value" => "datatype")));
  		$form->addElement(new Element_Textbox("Default value:", "content_field_value", array("value" => "value")));
  		$form->addElement(new Element_Button);
  		$form->configure(array(
  				"action" => "content/content_forms_add_type_field",
  				"method" => "post"
  		));
  	
  	$output = $form->render(true);
  	print $output;
  }
  
  // Method of the class
  function content_forms_edit_field($field) {
  	// Returns a string with the properties value. Uppercase the first character of each word
  	$output = 'soething here';
  	return;
  }
  
}


?>

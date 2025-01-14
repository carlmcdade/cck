<!-- template page_admin-->
<?php echo '<!-- <pre>'.print_r($_SESSION, 1).'</pre>-->';


if(isset($_SESSION['UserData'])){
    $content = '<div style="" class="alert-boxes">'. $content;
  
if(isset($_SESSION['UserData']['approved']) == $loggedInUser)
{
    $loggedInAs = $_SESSION['UserData']['UserName'];
}else{
    $loggedInAs = 'Guest';
}


$content = '<div>
  <a title="click here for log in" id="myWish" href="javascript:;" class="btn btn-secondary">Logged in as: '.$loggedInAs.'</a>
</div>
<div class="alert alert-secondary" id="message-alert"><pre>'. print_r($_SESSION, 1).
'</pre><form method="POST" name="form_log_out"><button name="user_logout" class="btn btn-secondary" type="submit" formaction="?admin/logout_user">log out</button>
    <input type="hidden" name="redirect_back" id="redirect-back" value= "'.
      (isset($POST['redirect_back']) ? $_POST['redirect_back'] : 'http://' . $_SERVER['HTTP_HOST'] . $INI['url']['frontpage']).'" />
    </form>
<div style="text-align: right;">
<button title="click here to close this form" name="close_form" id="close-form" type="button" class="btn btn-secondary " data-dismiss="alert"> close form </button>
</div>
</div><hr>'. $content;

} else {

    $content = '<div style="" class="alert-boxes">
<div>
    <a title="click here for log in" id="myWish" href="javascript:;" class="btn btn-mini ">Login as Administrator</a>
</div>
<div class="alert alert-secondary" id="message-alert">'. $CCK->_view('forms_admin_login', $VAR).'<br>
  <div style="text-align: right;">
      <button title="click here to close this form" name="close_form" id="close-form" type="button" class="btn btn-secondary " data-dismiss="alert"> close form </button>
  </div>
</div><hr>'. $content;


}


?>

<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8" />
<title>CCK | <?php echo(isset($pageTitle) ? $pageTitle : ''); ?></title>
<meta name="description" content="CCK is a PHP framework for web developers to build on.">
<meta name="keywords" content=" cck, drupal, wordpress, framework, cms, hosting, webhosting, server, php, servage">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="apple-touch-icon" sizes="180x180" href="images/favicon/apple-touch-icon.png">
<link rel="icon" type="image/png" sizes="32x32" href="images/favicon/favicon-32x32.png">
<link rel="icon" type="image/png" sizes="16x16" href="images/favicon/favicon-16x16.png">
<link rel="manifest" href="/site.webmanifest">

<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">    
<link href="https://vjs.zencdn.net/8.16.1/video-js.css" rel="stylesheet" />
<script src="js/jquery-3.7.1.min.js"></script>
<script src="js/cck.js"></script>
<script>

var form = document.forms.namedItem("content_type");

async function sendData() {
  // Associate the FormData object with the form element
  const formData = new FormData(form);

  try {
    const response = await fetch("?admin/content_type_field_save", {
      method: "POST",
      // Set the FormData instance as the request body
      body: formData,
    });
    console.log(await response.json());
  } catch (e) {
    console.error(e);
  }
}

// Take over form submission
form.addEventListener("submit", (event) => {
  event.preventDefault();
  sendData();
});

function makeid(length) {
    let result = '';
    const d = new Date();
    let time = d.getTime();

    const characters = time +'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    const charactersLength = characters.length;
    let counter = 0;
    while (counter < length) {
      result += characters.charAt(Math.floor(Math.random() * charactersLength));
      counter += 1;
    }
    return result;
}

function addSelectOption(selectBody){

      var optionName = document.getElementById(selectBody);
      var typeName = document.getElementById('content-type-name').value;
      var typeID = document.getElementById('content-type-id').value;
      var typeForm = document.forms.namedItem("content-type");
      var enumerate = "" + makeid(6);
      
      

        var addOptionLabel = document.createElement("INPUT");
        addOptionLabel.setAttribute("type", "text");
        addOptionLabel.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ selectBody+"][options]["+ enumerate +"][option_label]");
        
        var addOptionLabelLabel = document.createElement("DIV");
        addOptionLabelLabel.innerHTML = "Option Label";

        
        var addOptionValue = document.createElement("INPUT");
        addOptionValue.setAttribute("type", "text");
        addOptionValue.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ selectBody +"][options]["+enumerate+"][option_value]");
        addOptionValue.setAttribute("id", "");

        var addOptionValueLabel = document.createElement("DIV");
        addOptionValueLabel.innerHTML = "Option Value";

        // the id of the datalist or select element for options
        var optionParent = document.createElement("INPUT");
        optionParent.setAttribute("type", "hidden");
        optionParent.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ selectBody+"][options]["+enumerate+"][content_type_field_id]");
        optionParent.setAttribute("value", selectBody);

        var optionMachineId = document.createElement("INPUT");
        optionMachineId.setAttribute("type", "hidden");
        optionMachineId.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ selectBody +"][options]["+enumerate+"][option_machine_id]");
        optionMachineId.setAttribute("value", "option-" + enumerate );

        
        typeForm.prepend(addOptionLabel);
        typeForm.prepend(addOptionLabelLabel);
        typeForm.prepend(addOptionValue);
        typeForm.prepend(addOptionValueLabel);
        typeForm.prepend(optionParent);
        typeForm.prepend(optionMachineId);
        


//alert('Option fields added to '  + selectBody);


}
function MyFunction(chkBox) {
    //alert("checked");
    //alert($('input#foo').val());
    var typeName = document.getElementById('content-type-name').value;
    var typeID = document.getElementById('content-type-id').value;
    var identifier = makeid(6);
    var typeForm = document.forms.namedItem("content-type");
    
    //alert(chkBox.name +' -- '+ typeName);
    //alert($('input[name=add_field_'+ chkBox.name +'_value]').val());

    if(chkBox.name == "textarea")
    {
        var x = document.createElement("TEXTAREA");
        x.setAttribute("type", chkBox.name);
        x.setAttribute("name", chkBox.name + "-" + identifier);
        x.setAttribute("id", chkBox.name + "-" + identifier);
        var xLabel = document.createElement("DIV");
        xLabel.innerHTML = chkBox.name;

        var conFieldTypeID = document.createElement("INPUT");
        conFieldTypeID.setAttribute("type", "hidden");        
        conFieldTypeID.setAttribute("name", "Posted-"+ typeName +"[new_fields][" + chkBox.name + "-" + identifier+"][content_type_id]");
        conFieldTypeID.setAttribute("value", typeID);
        conFieldTypeID.setAttribute("type", "hidden");

        var conFieldMachineID = document.createElement("INPUT");
        conFieldMachineID.setAttribute("type", "hidden");        
        conFieldMachineID.setAttribute("name", "Posted-"+ typeName +"[new_fields][" + chkBox.name + "-" + identifier+"][machine_id]");
        conFieldMachineID.setAttribute("value", typeName + "-" + makeid(4) + "-" + makeid(4) );
        conFieldMachineID.setAttribute("type", "hidden");

        var field_name = document.createElement("INPUT");
        field_name.setAttribute("type", "hidden");
        field_name.setAttribute("name", "Posted-"+ typeName +"[new_fields][" + chkBox.name + "-" + identifier+"][field_name]");
        field_name.setAttribute("value", typeName + identifier + "-"+ chkBox.name);

        var field_label = document.createElement("INPUT");
        field_label.setAttribute("type", "hidden");        
        field_label.setAttribute("name", "Posted-"+ typeName +"[new_fields][" + chkBox.name + "-" + identifier+"][field_label]");
        field_label.setAttribute("value", "field_label");
        field_label.setAttribute("type", "hidden");

        var field_type = document.createElement("INPUT");
        field_type.setAttribute("type", "hidden");        
        field_type.setAttribute("name", "Posted-"+ typeName +"[new_fields][" + chkBox.name + "-" + identifier+"][field_type]");
        field_type.setAttribute("value", chkBox.name);
        field_type.setAttribute("type", "hidden");

        // clear varaibles that are not useed for this field type
        var addOptionLabel = "";
        var addOptionLabelLabel = "";
        var addOptionValue = "";
        var addOptionValueLabel = "";
        var optionParent = "";
        var optionMachineId = "";
        var optionAddButton = "";
        var newOption = "";
        var optionText = "";
        
    }
    else if(chkBox.name == "select" || chkBox.name == "datalist")
    {
        var x = document.createElement("SELECT");
        x.setAttribute("type", chkBox.name);
        x.setAttribute("name", chkBox.name + identifier);
        x.setAttribute("id", chkBox.name + identifier);

        var xLabel = document.createElement("DIV");
        xLabel.innerHTML = chkBox.name;

        var addOptionLabel = document.createElement("INPUT");
        addOptionLabel.setAttribute("type", "text");
        addOptionLabel.setAttribute("name", "Posted-"+ typeName +"[new_fields][" + chkBox.name + "-" + identifier+"][options]["+identifier+"][option_label]");
        
        var addOptionLabelLabel = document.createElement("DIV");
        addOptionLabelLabel.innerHTML = "Option Label";
        
        var addOptionValue = document.createElement("INPUT");
        addOptionValue.setAttribute("type", "text");
        
        addOptionValue.setAttribute("name", "Posted-"+ typeName +"[new_fields][" + chkBox.name + "-" + identifier+"][options]["+identifier+"][option_value]");
        addOptionValue.setAttribute("id", "");
        var addOptionValueLabel = document.createElement("DIV");
        addOptionValueLabel.innerHTML = "Option Value";

        var optionParent = document.createElement("INPUT");
        optionParent.setAttribute("type", "hidden");
        optionParent.setAttribute("name", "Posted-"+ typeName +"[new_fields][" + chkBox.name + "-" +identifier+"][options]["+identifier+"][content_type_field_id]");
        optionParent.setAttribute("value", chkBox.name + "-"  +identifier);

        var optionMachineId = document.createElement("INPUT");
        optionMachineId.setAttribute("type", "hidden");
        optionMachineId.setAttribute("name", "Posted-"+ typeName +"[new_fields][" + chkBox.name +"-"+identifier+"][options]["+identifier+"][option_machine_id]");
        optionMachineId.setAttribute("value", "option" +  "-" + identifier );

        var optionAddButton = document.createElement("INPUT");
        optionAddButton.setAttribute("type", "button");
        optionAddButton.setAttribute("name", "Posted-"+ typeName +"[new_fields][" + chkBox.name + "-" + identifier+"][add_button]");
        optionAddButton.setAttribute("value", "Add more options");
        optionAddButton.setAttribute("onclick", "addSelectOption('" + chkBox.name + "-" + identifier + "');");
        

        var newOption = document.createElement('OPTION');
        var optionText = document.createTextNode('Option Text');
        // set option text
        newOption.appendChild(optionText);
        // and option value
        newOption.setAttribute('value','Option Value');

        x.appendChild(newOption);
        

        var conFieldTypeID = document.createElement("INPUT");
        conFieldTypeID.setAttribute("type", "hidden");        
        conFieldTypeID.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ chkBox.name + "-" + identifier+"][content_type_id]");
        conFieldTypeID.setAttribute("value", typeID);
        conFieldTypeID.setAttribute("type", "hidden");

        var conFieldMachineID = document.createElement("INPUT");
        conFieldMachineID.setAttribute("type", "hidden");        
        conFieldMachineID.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ chkBox.name + "-" + identifier+"][machine_id]");
        conFieldMachineID.setAttribute("value", typeName + "-" + makeid(4) + "-" + makeid(4) );
        conFieldMachineID.setAttribute("type", "hidden");

        var field_name = document.createElement("INPUT");
        field_name.setAttribute("type", "hidden");
        field_name.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ chkBox.name + "-" + identifier+"][field_name]");
        field_name.setAttribute("value", typeName +"-"+ identifier + "-"+ chkBox.name);

        var field_label = document.createElement("INPUT");
        field_label.setAttribute("type", "hidden");        
        field_label.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ chkBox.name + "-" + identifier+"][field_label]");
        field_label.setAttribute("value", "field_label");
        field_label.setAttribute("type", "hidden");

        var field_type = document.createElement("INPUT");
        field_type.setAttribute("type", "hidden");        
        field_type.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ chkBox.name + "-" + identifier+"][field_type]");
        field_type.setAttribute("value", chkBox.name);
        field_type.setAttribute("type", "hidden");
        
    }
    
    else
    {
        var x = document.createElement("INPUT");
        x.setAttribute("name", chkBox.name + identifier);
        x.setAttribute("id", chkBox.name + "-" + identifier);
        

        var conFieldMachineID = document.createElement("INPUT");
        conFieldMachineID.setAttribute("type", "hidden");        
        conFieldMachineID.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ chkBox.name + "-" + identifier+"][machine_id]");
        conFieldMachineID.setAttribute("value", typeName + "-" + makeid(4)+"-"+ makeid(4) );
        conFieldMachineID.setAttribute("type", "hidden");

        var conFieldTypeID = document.createElement("INPUT");
        conFieldTypeID.setAttribute("type", "hidden");        
        conFieldTypeID.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ chkBox.name + "-" + identifier+"][content_type_id]");
        conFieldTypeID.setAttribute("value", typeID);
        conFieldTypeID.setAttribute("type", "hidden");

        var field_type = document.createElement("INPUT");
        field_type.setAttribute("type", "hidden");        
        field_type.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ chkBox.name + "-" + identifier+"][field_type]");
        field_type.setAttribute("value", chkBox.name);
        field_type.setAttribute("type", "hidden");

        var field_label = document.createElement("INPUT");
        field_label.setAttribute("type", "hidden");        
        field_label.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ chkBox.name + "-" + identifier+"][field_label]");
        field_label.setAttribute("value", "field_label");
        field_label.setAttribute("type", "hidden");

        var field_name = document.createElement("INPUT");
        field_name.setAttribute("type", "hidden");
        field_name.setAttribute("name", "Posted-"+ typeName +"[new_fields]["+ chkBox.name + "-" + identifier+"][field_name]");
        field_name.setAttribute("value", typeName + "-" + identifier + "-"+ chkBox.name);
        field_name.setAttribute("id", chkBox.name);

        var xLabel = document.createElement("DIV");
        xLabel.innerHTML = chkBox.name;
        x.setAttribute("type", chkBox.name);
        if(chkBox.name == "checkbox" || chkBox.name == "radio"){

          x.setAttribute("checked", true);
          

        }
        // clear variable that are not used for this field type to stop undefined errors
        var addOptionLabel = "";
        var addOptionLabelLabel = "";
        var addOptionValue = "";
        var addOptionValueLabel = "";
        var optionParent = "";
        var optionMachineId = "";
        var optionAddButton = "";
        var newOption = "";
        var optionText = "";
        
    }
    x.setAttribute("value", "");
    x.setAttribute("placeholder", "Save the content type to add this field");
    
    //x.setAttribute("id", "new-field-" + chkBox.name + "");
    document.forms.namedItem("content-type").prepend(x);
    document.forms.namedItem("content-type").prepend(xLabel);
    
    if (typeof conFieldMachineID !== 'undefined' || conFieldMachineID !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(conFieldMachineID);
    }
  
    if (typeof conFieldTypeID !== 'undefined' || conFieldTypeID !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(conFieldTypeID);
    }
    
    if (typeof field_name !== 'undefined' || field_name !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(field_name);
    }
    if (typeof field_label !== 'undefined' || field_label !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(field_label);
    }

    if (typeof field_type !== 'undefined' || field_type !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(field_type);
    }

    if (typeof addOptionLabel !== 'undefined' || addOptionLabel !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(addOptionLabel);
    }

    if (typeof addOptionLabelLabel !== 'undefined' || addOptionLabelLabel !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(addOptionLabelLabel);
    }

    if (typeof addOptionValue !== 'undefined' || addOptionValue !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(addOptionValue);
    }
    
    if (typeof addOptionValueLabel !== 'undefined' || addOptionValueLabel !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(addOptionValueLabel);
    }
    
    if (typeof optionParent !== 'undefined' || optionParent !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(optionParent);
    }
    
    if (typeof optionMachineId !== 'undefined' || optionMachineId !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(optionMachineId);
    }
    if (typeof optionAddButton !== 'undefined' || optionAddButton !== 'null') {
      // variable is undefined or null
      document.forms.namedItem("content-type").prepend(optionAddButton);
    }
    
    
    
    
    
} 

</script>
</head>

<body>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/quill@2.0.2/dist/quill.js"></script>
<div class="container my-5">

<div class="col-lg-8 px-0">
<h1><?php echo(isset($pageTitle) ? $pageTitle : ''); ?></h1>

<?php if (isset($mainNavigation)) {
    echo $mainNavigation;
}
?>

  
<!-- /#banner -->
<div style="text-align:right;">
<div class="btn-group">
<!-- sub navigation  -->
<?php if (isset($subNavigation)) {
    echo $subNavigation;
}
?>


<?php if (isset($adminNavigation)) {
    echo $adminNavigation;
}
?>
</div></div>

<?php

$clearSpace = array("_", "-");
$contentTitle = str_replace($clearSpace, " ", $contentTitle);
$frontCheck = '?'. $_SERVER['QUERY_STRING'];
if ($frontPage == $frontCheck || $urlSection == 'admin' || $urlSection == 'users') {
    $content =  '<h1 class="mt-2 text-center border border-secondary border-start-0 border-end-0" style="">' .(isset($contentTitle) ? $contentTitle : '') .'</h1>' .$content;
} else {
    $content =  '<h1 class="mt-2 text-center border border-secondary border-start-0 border-end-0" style="">' .(isset($contentTitle) ? $contentTitle : '') .'</h1>' .$content;
}
?>
<?php echo(isset($content) ? $content : ''); ?>
        
    <!-- /#content -->
<!-- footer -->
    <?php

       if ((require 'default_footer.tpl.php') == true) {
           echo '<!-- default_footer -->';
           //exit;
       }
?>

          </div>
</div> 
<style>
  <?php require("css/admin.css"); ?>
</style>
<?php //require("js/default.js");?>
</body>
</html> 

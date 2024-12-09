Content Connection Kit
========


If you are a web developer that is tired of Wordpress and Drupal and want something that is object oriented and actually made to be modified then keep checking in here. Berlinto is coming.
Features:

    A very short learning curve, one that does not require books or hundreds of reading hours.
    Easy to deploy. Deploying a CCK project is as easy as uploading it to the server because there is minimal use of database based core systems.
    Easy to upgrade. Upgrading is simple and in most cases unnecessary because CCK is lightweight and is an architecture style not a bloated CMS or Framework.
    Finding what you need and modification is easy. The Content Connection Kit's strength lies in it's code flexibilty, it is designed to be "hacked" by web programmers.
    Programmers can actually design and build their own "core" systems without fear of dependancy hell.
    Using third party classes and loosely coupled frameworks and libraries like Zend framework, Symfony components and EZ components is a snap.

Demo: http://hardcopy.free.nf

All this makes the Content Connection Kit a very flexible and robust web architecture that can be used to build most any web application to your liking.
Requirements:

    -PHP version 8
    -sqlite3
    -Bootstrap5 CSS
    
Features out of the box:

    _blog
    _event calendar
    _user configurable content types
    _user configurable fields
    _php templating system
    _php module system buit on Object oriented classes and methods
    

Architecture:

    _configuration
        config.ini
    _controllers
        [module]
            [module].class.inc
            [module]_[type].class.inc
            [module]_config.ini
    _helpers
    _models
    _views
        themes
            [theme]
                template.tpl.php
    css
    images
    js
    sass
    bootstrap.php
    index.php
    web.config
    .htaccess

Configuration:

    name = "Content Connection Kit"
    description = "Web Architecture for Web Developers"
    version = "1.x"


    [paths]

    controllers = "_controllers"
    models = "_models"
    views = "_views"
    helpers = "_helpers"

    [modules]

    module[] = "blog"
    module[] = "portfolio"
    module[] = "forum"
    module[] = "content"
    module[] = "contact"


    [hooks] 

    hook[] = "hook_links"
    hook[] = "hook_forms"
    hook[] = "hook_content"
    hook[] = "hook_blocks"
    hook[] = "hook_access"
    hook[] = "hook_admin_links"
    
    [themes] 

    theme[] = "theme_a"
    theme[] = "theme_b"
    theme[] = "theme_c"
    theme[] = "theme_d"
    
TODO:

<ul>
<li> Complete Content Class </li>
<li> Complete Blog Class</li>
</ul>

You can take a look at the Development Demo of the Content Connetion Kit which is live site that shows the result of the working code. Of course later on there will be a Git Hub repository where you can dowload the code.
The CCK project is owned and operated by 2010 — Carl McDade — All rights reserved.


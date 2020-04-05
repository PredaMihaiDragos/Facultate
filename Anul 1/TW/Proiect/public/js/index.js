/*let MainFramePage = {
    "button_acasa":"home.html",
    "button_orar":"orar.html",
    "button_programari":"programari.html",
    "button_despre":"despre.html",
    "button_rezultate":"rezultate.html",
    "button_certificari":"certificari.html",
    "button_chestionar":"chestionar.html",
    "button_contact":"contact.html"
};

var activeMenuButton = "button_acasa";

function UpdateMainFrame(id)
{
    if(!id)
        id = "button_acasa";
    if(id != activeMenuButton)
    {
        let activeClass = "menuButton_active";
        document.getElementById(activeMenuButton).classList.remove(activeClass);
        activeMenuButton = id;
        document.getElementById(activeMenuButton).classList.add(activeClass);

        document.getElementById("mainFrame").contentWindow.location.replace(MainFramePage[id]);
    }
}

function menuButtonClick()
{
    UpdateMainFrame(this.id);
}
*/
let navbar, body, sticky;

function init()
{
    navbar = document.getElementById("navbar");
    body = document.getElementsByTagName("BODY")[0];
    sticky = navbar.offsetTop;
    Scroll();
}

window.onscroll = function() {Scroll()};

function Scroll() 
{
    if (window.pageYOffset >= sticky) 
    {
        navbar.classList.add("sticky");
        body.classList.add("fixedNavbar");
        isSticky = false;
    } 
    else if(window.pageYOffset < sticky)
    {
        navbar.classList.remove("sticky");
        body.classList.remove("fixedNavbar");
        isSticky = true;
    }
}
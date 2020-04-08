let navbar, body, sticky;

function init()
{
    navbar = document.getElementById("navbar");
    sticky = 150;
    Scroll();
    initStarRating();
}

window.onscroll = function() {Scroll()};

function Scroll() 
{
    if (window.pageYOffset >= sticky) 
    {
        navbar.classList.add("sticky");
        isSticky = false;
    } 
    else if(window.pageYOffset < sticky)
    {
        navbar.classList.remove("sticky");
        isSticky = true;
    }
}

function scrollToTarget(id)
{
    const element = document.getElementById(id);
    const headerOffset = 70;
    const style = window.getComputedStyle(element);
    const marginTop = style.getPropertyValue('margin-top'); 
    const elementPosition = element.offsetTop - parseInt(marginTop);
    const offsetPosition = elementPosition - headerOffset;

    window.scrollTo({
         top: offsetPosition,
         behavior: "smooth"
    });
}

function GetResults()
{
    const id = document.getElementById("rezultate_id").value;
    const cnp = document.getElementById("rezultate_cnp").value;
    const pdfWindow = window.open("/get_bilet?cnp="+cnp+"&id="+id);
}


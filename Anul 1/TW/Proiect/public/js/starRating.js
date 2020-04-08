const STARS = 5;

class starRatingElem
{
    constructor(parent)
    {
        this.parent = parent;
        for(let i = 0; i < STARS; ++i)
        {
            const radio = document.createElement("i");
            radio.classList.add("fas");
            radio.classList.add("fa-star");
            radio.classList.add("radioStar");
            radio.onclick = function(elem) { starRatingElem.Click(elem); };
            radio.onmouseover = function(elem) { starRatingElem.MouseOver(elem); };
            radio.onmouseout = function(elem) { starRatingElem.MouseOut(elem); };
            elem.appendChild(radio);
        }
    }
    static Click(elem)
    {
        elem = elem.target;
        const children = elem.parentNode.childNodes;
        let i = 0;
        do
        {
            const child = children[i];
            child.classList.add("radio-checked");
        }
        while(children[i++] != elem);
    
        while(i < STARS)
        {
            const child = children[i];
            child.classList.remove("radio-checked");
            i++;
        }
    }
    static MouseOver(elem)
    {
        elem = elem.target;
        const children = elem.parentNode.childNodes;
        let i = 0;
        do
        {
            const child = children[i];
            child.classList.add("radio-hover")
        }
        while(children[i++] != elem);
    
        while(i < STARS)
        {
            const child = children[i];
            child.classList.add("radio-not-hover");
            i++;
        }
    }
    static MouseOut(elem)
    {
        elem = elem.target;
        const children = elem.parentNode.childNodes;
        let i = 0;
        while(i < STARS)
        {
            const child = children[i];
            child.classList.remove("radio-hover");
            child.classList.remove("radio-not-hover");
            i++;
        }
    }
}

starRating_elements = {};
function starRating_add(container)
{
    starRating_elements[container.id] = new starRatingElem(container);
}
function starRating_get(id)
{
    return starRating_elements[id];
}

function initStarRating()
{
    const elements = document.getElementsByClassName('starRating');
    for(elem of elements)
    {
        starRating_add(elem);
    }
}
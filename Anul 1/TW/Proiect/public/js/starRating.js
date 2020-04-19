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
        this.emoji = document.createElement("i");
        this.emoji.classList.add("radioEmoji");
        this.emoji.classList.add("far");
        this.emoji.classList.add("fa-meh");
        elem.appendChild(this.emoji);
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
        starRating.get(elem.parentNode.id).UpdateEmoji();
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
    SetStars(val)
    {
        if(val == null)
            return;
        starRatingElem.Click({target: this.parent.childNodes[val]});
    }
    GetStars()
    {
        let ret = 0;
        const children = this.parent.childNodes;
        let i = 0;
        while(i < STARS)
        {
            const child = children[i];
            if(child.classList.contains("radio-checked"))
                ret++;
            i++;
        }
        return ret;
    }
    UpdateEmoji()
    {
        const stars = this.GetStars();
        this.emoji.classList.remove("fa-frown");
        this.emoji.classList.remove("fa-meh");
        this.emoji.classList.remove("fa-smile");
        if(stars == 1 || stars == 2)
        {
            this.emoji.classList.add("fa-frown");
            this.emoji.style.color = "red";
        }
        else if(stars == 3)
        {
            this.emoji.classList.add("fa-meh");
            this.emoji.style.color = "yellowgreen";
        }
        else
        {
            this.emoji.classList.add("fa-smile");
            this.emoji.style.color = "green";
        }
    }
}

class starRatingClass
{ 
    constructor()
    {
        this.elements = {};
    }
    add(container)
    {
        this.elements[container.id] = new starRatingElem(container);
    }
    get(id)
    {
        return this.elements[id];
    }
};

const starRating = new starRatingClass();

function initStarRating()
{
    const elements = document.getElementsByClassName('starRating');
    for(elem of elements)
    {
        starRating.add(elem);
    }
}
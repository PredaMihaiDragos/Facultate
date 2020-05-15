function Info(text, okText = "OK") //myalert_a
{
    let wrapper = document.createElement("div");
    wrapper.classList.add("infoAlertWrapper");
    let div = document.createElement("div");
    div.classList.add("infoAlert");
    div.innerHTML = text;
    let okButton = document.createElement("button");
    okButton.classList.add("infoAlert-okButton");
    okButton.innerHTML = okText;
    okButton.onclick = function() {
        document.body.removeChild(wrapper);
    };

    div.appendChild(okButton);
    wrapper.appendChild(div);
    document.body.appendChild(wrapper);  
}

function Error(text, okText = "OK") //myalert_b
{
    let wrapper = document.getElementById("errorAlertWrapper");
    let div = document.getElementById("errorAlert");
    let okButton = document.getElementById("errorAlert-okButton");
    let textDiv = document.getElementById("errorAlert-text");
    textDiv.innerHTML = text;
    okButton.innerHTML = okText;
    wrapper.style.display = "inline";
    okButton.onclick = function() {
        wrapper.style.display = "none";
    };
}
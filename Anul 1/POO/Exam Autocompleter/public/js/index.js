const editor = CodeMirror.fromTextArea(document.getElementById('input_code'), {
    autoCloseBrackets : true,
    mode : "text/x-c++src",
    lineNumbers : true,
    matchBrackets : true,
    indentUnit: 4
  });
  const results = CodeMirror.fromTextArea(document.getElementById('results'), {
    autoCloseBrackets : true,
    mode : "text/x-c++src",
    lineNumbers : true,
    matchBrackets : true,
    indentUnit: 4
  //  readOnly: true
  });

const UPDATE_TIME = 500;

function Init()
{
    setInterval(function() { 
        GetUpdates();
    }, UPDATE_TIME);
}

let lastUpdate = "";

function Update()
{
    let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) 
    {
        if(this.status == 200)
        {
          
        }
        else
        {
          console.log(this.responseText);
        }
    }
  };
  xhttp.open("POST", "/update", true);
  xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  xhttp.send("json=" + editor.getValue());
}

function GetUpdates()
{
    if(lastUpdate == editor.getValue())
      return;
    let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) 
      {
          if(this.status == 200)
          {
              results.setValue(this.responseText);
          }
          else
          {
            console.log(this.responseText);
          }
      }
    };
    lastUpdate = editor.getValue();
    xhttp.open("POST", "/get", true);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send("json=" + editor.getValue());
}
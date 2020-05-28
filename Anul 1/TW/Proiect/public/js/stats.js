function Init()
{
    const currentDate = new Date();
    let weekAgoDate = new Date();
    weekAgoDate.setDate(weekAgoDate.getDate() - 7);
    document.getElementById("inputEnd").value = currentDate.toISOString().slice(0,10);
    document.getElementById("inputStart").value = weekAgoDate.toISOString().slice(0,10);
}
function addFilterForm(){
    $("<form>").attr({id: "filterOptions"}).appendTo($("#filterEvents"));
    $("<input>General").attr({"value": '1', type: "radio", class: "opt"}).appendTo($("#filterOptions"));
    $("<input>Meeting").attr({"value": '2', type: "radio", class: "opt"}).appendTo($("#filterOptions"));
    $("<input>Conference").attr({"value": '3', type: "radio", class: "opt"}).appendTo($("#filterOptions"));
    $("<input>Presentation</input>").attr({"value": '4', type: "radio", class: "opt"}).appendTo($("#filterOptions"));
    $("<input>Lecture</input>").attr({"value": '5', type: "radio", class: "opt"}).appendTo($("#filterOptions"));
    $("<input>Party</input>").attr({"value": '6', type: "radio", class: "opt"}).appendTo($("#filterOptions"));
    $("<input>Birthday</input>").attr({"value": '7', type: "radio", class: "opt"}).appendTo($("#filterOptions"));
    $("br").appendTo($("#filterOptions"));
    $("<input>Other</input>").attr({"value": '8', type: "radio", class: "opt"}).appendTo($("#filterOptions"));
    .each()
    
}
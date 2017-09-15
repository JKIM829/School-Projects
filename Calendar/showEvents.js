function getEvents(){
    var dataString = "month=" + encodeURIComponent(currentMonth.month+1) + "&year=" + encodeURIComponent(currentMonth.year) + "&tok=" + encodeURIComponent(tok);
	$.ajaxSetup({
		async:false
	});
	$.ajax({
		type: "POST",
		url: "getEvents.php",
        data: dataString,
        dataType: "json",
		success:function(data){
            if(data.success){
                tok = data.tok;
                result = data.events;
            }
            else{
                tok = data.tok;
                result = false;
            }
		},
        error: function(data){
            alert(data.message);
            result = false;
        }
	});
	$.ajaxSetup({
		async:true
	});
    
    if(result===null){
		result = false;
	}
    
	return result;
}

function load_Dialog(){
    $('.confirmation').dialog({
		autoOpen: false,  
        modal: true,
		});
   
	$('.Event').each(function() {  
    $.data(this, 'dialog', 
      $(this).next('.dialog').dialog({
        autoOpen: false,  
        modal: true,
		buttons:[
            {text: "Edit Event",
            "data-jq-dropdown":"#jq-dropdown-1",
            click: function(){
                var id =  $(this).attr("value");
                $('#edit').attr("value", id);
            }
            },
            {text: "Delete Event",
            click: function() {
				var id =  $(this).attr("value");
				$(this).dialog('close');
                $('.confirmation').attr("title", "Confirmation");
                $('.confirmation').html("Are you sure you want to delete this event?");
				$('.confirmation').dialog("open");
                $('.confirmation').dialog({
                    resizable: false,
                    height:    125,
                    width:     300,
                    modal:     true,
                    buttons:  {
                    'Delete': function() {
                        deleteEvent(id);
                        $(this).dialog('close');
                    },
					'Cancel': function(){
						$(this).dialog('close');
					}
                }
			});
			}},
            {text: "Close",
                click: function(){$(this).dialog('close');} 
            }
			]
      })
    );
  }).click(function() {
      $.data(this, 'dialog').dialog('open');
    });
}
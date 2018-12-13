$(document).ready(function(){

	setBindings();

})

function setBindings(){
	$("ul a").click(function(e){
		e.preventDefault();
		var sectionID = e.currentTarget.id + "Section";

		$("html body").animate({
			scrollTop: $("#" + sectionID).offset().top - $("#" + sectionID).height() / 10
		}, 2500);

	})

}

function fav_display(fav_flag) {
    if (fav_flag == 0) {
        $('.item-list', '.block-favorites').fadeIn();
        fav_flag = 1;
    }
    if (fav_flag == 1) {
        $('.item-list', '.block-favorites').fadeOut();
    }
}

$(document).ready(function(){
   $('.dish-gallery img').click(function(){
       $('#dish-thumbnail').html('<img src="'+$(this).attr('src')+'"/>');
   });
   
   var fav_flag = 0;
   //add to my favorites
   $('.block-favorites .item-list').fadeOut();
   $('.block-favorites h2').click(function(){
        if (fav_flag == 0) {
            $('.item-list', '.block-favorites').fadeIn();
            fav_flag = 1;
        }
        else if (fav_flag == 1) {
            $('.item-list', '.block-favorites').fadeOut();
            fav_flag = 0;
        }
       
   });
});
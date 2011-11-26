function slideshow() {
    $('.view-display-id-block_1 .view-content').cycle({
        fx:     'fade',
        speed:  'slow',
        timeout: 5000,
        pager:  '#slider_nav',
        pagerAnchorBuilder: function(idx, slide) {
            // return sel string for existing anchor
            return '#slider_nav li:eq(' + (idx) + ') a';
        }
    });
}
function main_menu_hover() {
    $('#main-menu a').hover(function(){
        $(this).animate({
            'opacity': '1'
        }, 'slow');
    },
    function(){
        $(this).animate({
            'opacity': '0.5'
        }, 'fast');
    }
    );
}
function news_page_actions(){
    $('.view-id-news.view-display-id-page_1 .views-row').click(function(){
        window.location.href = $('.views-field-title a',this).attr('href');
    });
}
$(document).ready(function(){
    news_page_actions();
    slideshow();
    main_menu_hover();
});
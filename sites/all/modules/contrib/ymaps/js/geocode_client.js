
/**
 * Location chooser interface.
 * (geocoding in browser, locpicking)
 */


//preparing all maps
var ymap = new Array();
var mark = new Array();
Drupal.behaviors.YmapsEditShow = function (context) {
   
  $("div[id*='locpick-user-longitude-wrapper']").each(function () {
    var domEl = $(this).get(0);
    var curId = domEl.id;

    var numId = getnumId(curId);
    //adding div for map
    $(this).after('<div id="ymaplocpick'+numId+'" class="form-item" style="height:300px"></div>');
    YMaps.load();
    initMapsLocpick(numId); 
    existingCoords (curId);

  });

listenFormChanges ()

};


//getting numeric id from complete form
function getnumId(allid) {
  var patt1 = /\d{1,}/g;
  return allid.match(patt1);
}


//initiation of maps
function initMapsLocpick (key) {
  ymap[key] = new YMaps.Map( document.getElementById("ymaplocpick"+key) );
  ymap[key].setCenter( new YMaps.GeoPoint( 36.27,49.980 ), 3, YMaps.MapType.MAP );
  ymap[key].addControl(new YMaps.TypeControl());
  //ymap[key].addControl(new YMaps.ToolBar());
  ymap[key].addControl(new YMaps.Zoom());

  YMaps.Events.observe(ymap[key],ymap[key].Events.Click, function (mEvent) {
    addMarker(key,mEvent.getGeoPoint());
  });
};


//moving old marker (if exist) and place new one
function addMarker (key,point) {
  //options for markers
  var markoptions = {
    draggable: 1,
    hasBalloon: false,
    hintOptions: {
      maxWidth: 100,
      showTimeout: 200,
      hintOffset: new YMaps.Size(5,5)
    }
  };
  if (mark[key]) {
    mark[key].setGeoPoint(point);
  }
  else { 
    mark[key] = new YMaps.Placemark(point,markoptions);  
    ymap[key].addOverlay(mark[key]);}
    //and centering map
    setCoords(key,point);
YMaps.Events.observe(mark[key],mark[key].Events.PositionChange, function (mEvent) {setCoords(key,mark[key].getGeoPoint());});   
}


//setting new coordianates for input fields
function setCoords (key,npoint) {
  $("input[id*='edit-locations-"+key+"-locpick-user-latitude']").attr("value", npoint.getLat());
  $("input[id*='edit-locations-"+key+"-locpick-user-longitude']").attr("value", npoint.getLng());
  ymap[key].panTo(npoint);
}


//checking for existing coordinates and adding initial marker
function existingCoords (locId) {
  //some bad synthetic way to know whether latitude exists
  var lat;
  var latdiv = $("div#"+locId).parent().children("fieldset").children("div:first"); 
  lat = latdiv.text().match(/-?\d{1,}.\d{1,}/g);
  if (lat) {
   //longitude also should be nearby
    var lon = latdiv.next("div").text().match(/-?\d{1,}.\d{1,}/g);
    
    
     addMarker(getnumId(locId), new YMaps.GeoPoint(lon, lat));
  }

}



//listening form events
function listenFormChanges () {
  var prefix = "[id*='edit-locations']";
  $("input"+prefix).bind("change", function(){
  var lid = getnumId(this.id);
  var address = 
		$("input"+prefix+"[id*='"+lid+"'][id*='city']").attr("value")+","+
                $("input"+prefix+"[id*='"+lid+"'][id*='street']").attr("value")+","+
                $("input"+prefix+"[id*='"+lid+"'][id*='additional']").attr("value");
  //geocoding
  geoCode(address, lid);
  });
}


//geocoding function
function geoCode (city,key) {
  var gcpoint;
  var geocoder = new YMaps.Geocoder(city);
  YMaps.Events.observe(geocoder, geocoder.Events.Load, function () {
    if (this.length()) {
      gcpoint = this.get(0).getGeoPoint();
      addMarker(key,gcpoint);
    }
  });
}
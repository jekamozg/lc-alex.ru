
/**
 * Track editing interface fro trackfield module
 * 
 */

//preparing all maps
var ymap = new Array();
var mark = new Array();
var track = new Array();
var trackpoints = new Array();
//options for markers
var trackmopts = {
draggable: 1,
hasBalloon: false,
};




//show or hide maps
function mapShowHide (fieldname, key) {
  var map = $("div#ymap-edit-track-field_"+fieldname+"-"+key);
  var selected = $("select[id*='edit-field'][id*='"+fieldname+"'][id*='"+key+"'] option:selected").val();  
  if (selected == 'latlon') {
    map.show("slow");
  }
  else {
    map.hide("slow");
  }

}



//initiation of maps
function initDrawTrack (fieldname, key) {
  var complkey = fieldname + key; 
  
  ymap[complkey] = new YMaps.Map( document.getElementById("ymap-edit-track-field_"+fieldname+"-"+key) );
  ymap[complkey].setCenter( new YMaps.GeoPoint( 36.27,49.980 ), 2, YMaps.MapType.MAP );
  ymap[complkey].addControl(new YMaps.TypeControl());
  ymap[complkey].addControl(new YMaps.Zoom());
  ymap[complkey].addControl(new YMaps.ToolBar());
  //ymap[complkey].enableRuler();
  ymap[complkey].listenMouseEvent;
  mark[complkey] = new Array();
  trackpoints[complkey] = new Array();
  YMaps.Events.observe(ymap[complkey],ymap[complkey].Events.Click, function (mEvent) {
  
  addMarkerToTrack(fieldname,key,mEvent.getGeoPoint());
 });
 existingTrack(fieldname,key);
 listenTrackFormChanges(fieldname, key);
};


//place new marker
function addMarkerToTrack (fieldname,key,point) {
  trackpoints[fieldname+key].push(point);
  trackRedraw(fieldname,key);
  //mark[complkey].push(new YMaps.Placemark(point,trackmopts));  
    //ymap[fieldname+key].addOverlay(mark[fieldname+key]);}
    //and centering map
    setTrackField(fieldname,key);
  
}


//setting new coordianates for input fields
function setTrackField (fieldname,key) { 
  $("textarea[id*='edit-field'][id*='"+fieldname+"'][id*='"+key+"']").val(pointsToCsv(trackpoints[fieldname+key]));
}


//checking for existing track and adding initial track
function existingTrack (fieldname,key) {
  if ($("textarea[id*='edit-field'][id*='"+fieldname+"'][id*='"+key+"']").val() != ""){

    trackpoints[fieldname+key] = csvToPoints($("textarea[id*='edit-field'][id*='"+fieldname+"'][id*='"+key+"']").val());
    trackRedraw(fieldname,key);
    ymap[fieldname+key].setBounds(new YMaps.GeoCollectionBounds(trackpoints[fieldname+key]));
  }
}


//listening form events
function listenTrackFormChanges (fieldname, key) {
  $("textarea[id*='edit-field'][id*='"+fieldname+"'][id*='"+key+"']").bind("change", function(){
  trackpoints[fieldname+key] = csvToPoints(this.value);
  trackRedraw(fieldname,key);
  });
}

//redraw existing track or create new one
function trackRedraw (fieldname,key) {
  var complkey = fieldname + key;
      jQuery.each(trackpoints[complkey], function(i, point) {
    //if (mark[complkey][i]) {
    //mark[complkey][i].setGeoPoint(trackpoints[complkey][i]);
    //}
    //else {
      mark[complkey][i] = new YMaps.Placemark(trackpoints[complkey][i],trackmopts);
      YMaps.Events.observe(mark[complkey][i],mark[complkey][i].Events.DragEnd, function (mEvent) {
      trackpoints[complkey][i].moveTo(mEvent.getGeoPoint());
      setTrackField(fieldname,key);
      });
      YMaps.Events.observe(mark[complkey][i],mark[complkey][i].Events.DblClick, function (mEvent) {
      trackpoints[complkey].splice(i,1); 
      trackRedraw(fieldname,key);
      setTrackField(fieldname,key);
      });

    //}
  });
  
  if (track[complkey]) {
    track[complkey].removeAll();
    ymap[complkey].removeOverlay(track[complkey])
  }
  else {
    track[complkey] = new YMaps.ConnectedPlacemarks(trstyle);
  }
  
  track[complkey].add(mark[complkey]); 
  ymap[complkey].addOverlay(track[complkey]);
  //don't change zoom with redraw
  //ymap[complkey].setBounds(new YMaps.GeoCollectionBounds(trackpoints[complkey]));
//   //var pl = new YMaps.Polyline(csvToPoints(this.value));
//   //ymap[complkey].addOverlay(pl);
//   //ymap[complkey].enableRuler;
//   //ymap[complkey].setRulerState(pointsToRuler(csvToPoints(this.value)));
}


//convert geopoints to csv
function pointsToCsv (points) {
  var linestring = "";
  for (var i=0; i< points.length ; i++) {
  linestring += points[i].getLat() +"," + points[i].getLng() +"\n";
  }
  return linestring;
}


//convert string CSV to geo points array
function csvToPoints (csvline) {

  var parsedline = csvToArray(csvline);
  var points = new Array();
  var lat;
  var lon; 
  //for ( var i in parsedline ){
  jQuery.each(parsedline, function(i, point) {
  //TODO checks vor validity
  
  lat = point[0];
  lon = point[1];
  
  points[i] = new YMaps.GeoPoint(lon,lat);
  }
  ); 
return points;
}

//convert geopoints array to Yandex ruler string
function pointsToRuler (points) {
  var originlat = points[0].getLat();
  var originlon = points[0].getLng();
  var rulerstring = points[0].toString(); 
  for (var i=1; i < points.length; i++) {
                    rulerstring += "~"+(points[i].getLng()-originlon)+","+(points[i].getLat()-originlat); 
  }
  return rulerstring;
}


  

//own csv parsing
function csvToArray (csvstring) {
  csvstring = jQuery.trim(csvstring);
  var linearray = csvstring.split(new RegExp("[\n\r]+"));
  var points = new Array();
  jQuery.each(linearray, function(i, line) {
  points[i] = parseCSVLine(line);
  });
  return points;
}

function parseCSVLine (line)
{
    var tmp = [];
    var inQuote = false;
    var parNum = 0;
    for (var i=0, len = line.length; i < len; i++)
    {
        var c = line.charAt(i);
        if (c == "'")
        {
            inQuote = !inQuote;
            if (!tmp[parNum]) tmp[parNum] = c;
            else tmp[parNum] += c;
        }
        else if (c == "," && !inQuote)
        {
            parNum++;
        }
        else if (c != ' ' || inQuote)
        {
            if (!tmp[parNum]) tmp[parNum] = c;
            else tmp[parNum] += c;
        }
    }

    return tmp;
};
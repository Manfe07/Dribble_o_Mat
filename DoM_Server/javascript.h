String javaScript;

void buildJavascript() {
  javaScript = "<SCRIPT>\n";
  javaScript += "xmlHttp=createXmlHttpObject();\n";

  javaScript += "function createXmlHttpObject(){\n";
  javaScript += "  if(window.XMLHttpRequest){\n";
  javaScript += "    xmlHttp=new XMLHttpRequest();\n";
  javaScript += "  }else{\n";
  javaScript += "    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n";
  javaScript += "  }\n";
  javaScript += "  return xmlHttp;\n";
  javaScript += "}\n";

  javaScript += "function process(){\n";
  javaScript += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  javaScript += "    xmlHttp.onreadystatechange=function(){\n";
  javaScript += "      if(xmlHttp.readyState==4&&xmlHttp.status==200){\n";
  javaScript += "        xmlDoc=xmlHttp.responseXML;\n";
  javaScript += "        xmlmsg=xmlDoc.getElementsByTagName('millistime')[0].firstChild.nodeValue;\n";
  javaScript += "        document.getElementById('runtime').innerHTML=xmlmsg;\n";
  javaScript += "        xmlmsg=xmlDoc.getElementsByTagName('mode')[0].firstChild.nodeValue;\n";
  javaScript += "        document.getElementById('gameMode').innerHTML=xmlmsg;\n";
  javaScript += "        xmlmsg=xmlDoc.getElementsByTagName('counter_1')[0].firstChild.nodeValue;\n";
  javaScript += "        document.getElementById('hits_1').innerHTML=xmlmsg;\n";
  javaScript += "        xmlmsg=xmlDoc.getElementsByTagName('counter_2')[0].firstChild.nodeValue;\n";
  javaScript += "        document.getElementById('hits_2').innerHTML=xmlmsg;\n";
  javaScript += "        xmlmsg=xmlDoc.getElementsByTagName('sensetivVal')[0].firstChild.nodeValue;\n";
  javaScript += "        document.getElementById('sensetiv').innerHTML=xmlmsg;\n";
  javaScript += "        xmlmsg=xmlDoc.getElementsByTagName('durationVal')[0].firstChild.nodeValue;\n";
  javaScript += "        document.getElementById('duration').innerHTML=xmlmsg;\n";
  javaScript += "      }\n";
  javaScript += "    }\n";
  javaScript += "    xmlHttp.open('PUT','xml',true);\n";
  javaScript += "    xmlHttp.send(null);\n";
  javaScript += "  }\n";
  javaScript += "  setTimeout('process()',50);\n";
  javaScript += "}\n";

  javaScript += "function duration_set(){\n";
  javaScript += "  durationVal=document.getElementById('duration').value;\n";
  javaScript += "  document.getElementById('duration').innerHTML=durationVal;\n";
  javaScript += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  javaScript += "    xmlHttp.open('PUT','setESPval?var=duration&val='+durationVal,true);\n";
  javaScript += "    xmlHttp.send(null);\n";
  javaScript += "  }\n";
  javaScript += "}\n";

  javaScript += "function sensetiv_set(){\n";
  javaScript += "  sensetivVal=document.getElementById('sensetiv').value;\n";
  javaScript += "  document.getElementById('sensetiv').innerHTML=sensetivVal;\n";
  javaScript += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  javaScript += "    xmlHttp.open('PUT','setESPval?var=sensetiv&val='+sensetivVal,true);\n";
  javaScript += "    xmlHttp.send(null);\n";
  javaScript += "  }\n";
  javaScript += "}\n";

  javaScript += "</SCRIPT>\n";
}

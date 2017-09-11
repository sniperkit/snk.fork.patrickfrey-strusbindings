comment //
template main ENDHTML {{ }}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html lang="en">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
	<title>Strus PHP interface documentation</title>
	<link rel="stylesheet" href="bindingsDocNav.css" type="text/css" />
</head>
<body onload="initLoad()">
<script type="text/javascript" src="bindingsDocNav.js"></script>

<div class="container">
<div class="product">
	<div class="product_logo"> <img class="product_logo_img" src="images/logotype.jpg" alt="Strus"/></div>
	<div class="product_name">{{project}} PHP Bindings</div>
	<div class="product_release">{{release}}</div>
	<div class="product_author">{{author}}</div>
	<div class="product_copyright">{{copyright}}</div>
	<div class="product_license">{{license}}</div>
	<div class="product_description">PHP interface for strus, a set of libraries and programs to build a text search engine</div>
</div> <!-- product -->
<!-- Menu -->
<div class="navigation">
<h1 class="maintitle">strus</h1>

<h2 id="nav_title_classes">Classes</h2>
<div class="navclasslist">
	{{navclasslist}}
</div>  <!-- navclasslist -->
{{navmemberlist}}
</div> <!-- navigation -->

<div class="content">
{{classdescription}}
{{memberdescription}}
</div> <!-- content -->

<div class="about">
<i>generated by papugaDoc ({{project}} {{release}})</i>
</div>

</div>
</body>
</html>
ENDHTML

group constructor method
namespace projectnamespace=project locase
variable project
variable author
variable copyright
variable license
variable release

namespace classname=class
index classidx=class {class}
template navclasslist=class END {{ }}
<div class="navclass" id="nav_{{classidx}}" onclick="activateClassNav('{{classidx}}');">{{classname}}</div>
END

template navmemberlist=class END {{ }}
<h3 class="nav_title_memberlist" id="title_{{classidx}}">{{classname}}</h3>
<div class="navmemberlist" id="list_{{classidx}}">
	{{navmember}}
</div> <!-- navmemberlist -->
END

index methodidx=method      {class} {constructor,method}
index methodidx=constructor {class} {constructor,method}

template navmember=method END {{ }}
<div class="navmethod" id="nav_{{methodidx}}" onclick="showMethod('{{methodidx}}')">{{methodname}}</div>
END
template navmember=constructor END {{ }}
<div class="navconstructor" id="nav_{{methodidx}}" onclick="showMethod('{{methodidx}}')">{{constructorname}}</div>
END

template classdescription=class END {{ }}
<div class="classdescription" id="description_{{classidx}}">
<h2 class="content_title">{{projectnamespace}}_{{classname}}</h2>
<p class="leadtext">
{{description}}
</p>
<div class="callremarks">{{remarks}}</div> <!-- callremarks -->
<div class="callnotes">{{notes}}</div> <!-- callnotes -->
</div> <!-- classdescription -->
END

template memberdescription=method END {{ }}
<div class="memberdescription" id="description_{{methodidx}}">
<h2 class="content_title">:{{methodname}}</h2>
<p class="text">
{{description}}
</p>
<h4 class="content_subtitle">Parameter</h4>
<div class="parameterlist">{{parameterlist}}</div>
{{callremarks}}
{{callnotes}}
{{callexamples}}
</div> <!-- memberdescription -->
END

template memberdescription=constructor END {{ }}
<div class="memberdescription" id="description_{{methodidx}}">
<h2 class="content_title">.{{constructorname}}</h2>
<p class="text">
{{description}}
</p>
<h4 class="content_subtitle">Parameter</h4>
<div class="parameterlist">{{parameterlist}}</div>
{{callremarks}}
{{callnotes}}
{{callexamples}}
</div> <!-- memberdescription -->
END

template callexamples=constructor END {{ }}
<h4 class="content_subtitle">Examples</h4>
<div class="callexamples">{{examples}}</div> <!-- callexamples -->
END

template callexamples=method END {{ }}
<h4 class="content_subtitle">Examples</h4>
<div class="callexamples">{{examples}}</div> <!-- callexamples -->
END

template callnotes=method END {{ }}
<h4 class="content_subtitle">Notes</h4>
<div class="callnotes">{{notes}}</div> <!-- callnotes -->
END

template callnotes=constructor END {{ }}
<h4 class="content_subtitle">Notes</h4>
<div class="callnotes">{{notes}}</div> <!-- callnotes -->
END

template callremarks=method END {{ }}
<h4 class="content_subtitle">Remarks</h4>
<div class="callremarks">{{remarks}}</div> <!-- callremarks -->
END

template callremarks=constructor END {{ }}
<h4 class="content_subtitle">Remarks</h4>
<div class="callremarks">{{remarks}}</div> <!-- callremarks -->
END

template parameterlist=param END {{ }}
<div class="param">
<div class="paramname">{{paramname}}</div>
<div class="paramdescr">{{paramdescr}}</div>
{{paramexamples}}
</div> <!-- param -->
END

empty parameterlist <div class="note">no parameters defined</div>

template paramexamples=param END {{ }}
<div class="paramexamples">{{examples}}</div> <!-- paramexamples -->
END

template notes=class END {{ }}
{{notelist}}
END
template remarks=class END {{ }}
{{remarklist}}
END

template notes=method END {{ }}
{{notelist}}
END
template remarks=method END {{ }}
{{remarklist}}
END

template notes=constructor END {{ }}
{{notelist}}
END
template remarks=constructor END {{ }}
{{remarklist}}
END

template notes=param ?notelist END {{ }}
<div class="annotation_subtitle">{{paramname}}</div>
<div class="annotation">{{notelist}}</div> <!-- annotation -->
END

template remarks=param ?remarklist END {{ }}
<div class="annotation_subtitle">{{paramname}}</div>
<div class="annotation">{{remarklist}}</div> <!-- annotation -->
END

template examples=usage END {{ }}
<div class="example">{{example}}</div>
END

template notelist=note END {{ }}
<div class="note">{{note}}</div>
END

template remarklist=remark END {{ }}
<div class="remark">{{remark}}</div>
END

variable constructorname=constructor
variable methodname=method
variable description=brief xmlencode
variable note=note xmlencode
variable remark=remark xmlencode
variable paramname=param[0]
variable paramdescr=param[1:] xmlencode
variable example=usage xmlencode
ignore url
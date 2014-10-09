;<html>
<!- Copyright (c) Go Ahead Software Inc., 1999-2010. All Rights Reserved. ->
<head>
<title>ASP Test Page</title>
<link rel="stylesheet" href="/style/normal_ws.css" type="text/css">
<% language=javascript %>
</head>

	<script language="javascript"> 
		function accept1(){ 
		 	<!--var v="<% aspVol(); %>";-->
			var v="<% aspGetInputVol(); %>";
			alert(v);
		} 
	</script>
		
<body>

<h1>ASP / JavaScript&#153; Test</h1>
<h2>Expanded ASP data: <% aspTest("Peter Smith", "112 Merry Way"); %></h2>

<P>
<% var z; \
   for (z=0; z<5; z=z+1) \
     { \
     if (z<=2) \
		write(z+" is less than 3<br>"); \
     else if (z==3) \
		write(z+" is equal to 3<br>"); \
     else \
		write(z+" is greater than 3<br>"); \
     } \
%>
</P>

<% aspVol(); %><br/>
<% aspGetInputVol(); %><br/>
<% aspGetBchEQ(); %><br/>
<% aspGetAchEQ0(); %><br/>
<% aspGetAchEQ1(); %><br/>
<% aspGetAchEQ2(); %><br/>
<% aspGetAchEQ3(); %><br/>
<% aspGetAchEQ4(); %><br/>
<% aspGetAchEQ5(); %><br/>
<% aspGetOutDly(); %><br/>
<% aspGetLimit(); %><br/>
<% aspGet3D(); %><br/>
<% aspGetSct(); %><br/>
<% aspGetHpf(); %><br/>
<% aspGetBpf(); %><br/>
<% aspGetAd(); %><br/>
<% aspGetOutMix(); %><br/>
<% aspGetOutVol(); %><br/>
<% aspGetVersion(); %><br/>

 

<span style="color:#3333ff;"><!-- added start for test upload file by gyr 2011.10.15 -->  
	<h1>GoForm Test</h1>  
	<form action=/goform/formTest method=POST>
		<table>
		<tr>
			<td>Name:</td>
			<td><input type=text name=name size=50 value=""></td>
		</tr>
		<tr>
			<td height="26">Address:</td>
			<td><input type=text name=address size=50 value=""></td>
		</tr>
		<tr>
		    <td></td>
		      <td ALIGN="CENTER"> 
		        <input type=submit name=ok value="OK"> <input type=submit name=ok value="Cancel"></td>
		</tr>
		</table>
	</form> 
	<!-- added end for test upload file by gyr 2011.10.15 -->  
</span> 


	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
		<h1>GoForm download</h1> 
		<form name="download" action="/goform/formDlownload" method="post" target="rfFrame">
			     <input name="" type="submit"/>
		</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
		<h1>GoForm all bypass</h1> 
		<form name="bypass" action="/goform/formAllByPass" method="post" target="rfFrame">
			     <input name="" type="submit"/>
		</form>
	<hr/>


	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
		<h1>GoForm show</h1> 
		<form name="show" action="/goform/formShowInfo" method="post" target="rfFrame">
			     <input name="" type="submit"/>
		</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
		<h1>GoForm Crossbar1</h1> 
		<form name="Crossbar1" action="/goform/formCrossbar1" method="post" target="rfFrame">
			rd:	 <input type="text"  name="rd"/><br/>
			in:<input type="text"  name="in"/><br/>
			out:  <input type="text"  name="out"/><br/>
			mix:<input type="text"  name="mix"/><br/>
			     <input name="" type="submit"/>
		</form>
	<hr/>
	
	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
		<h1>GoForm ACHEQ</h1> 
		<form name="peq" action="/goform/formACHEQ" method="post" target="rfFrame">
			Q:	 <input type="text"  name="Q"/><br/>
			Gain:<input type="text"  name="Gain"/><br/>
			Fc:  <input type="text"  name="Fc"/><br/>
			Type:<input type="text"  name="Type"/><br/>
			En:  <input type="text"  name="En"/><br/>
			no:  <input type="text"  name="no"/><br/>
			Ch:  <input type="text"  name="Ch"/><br/>
			     <input name="" type="submit"/>
		</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm BCHEQ</h1> 
	<form name="peq" action="/goform/formBCHEQ" method="post" target="rfFrame">
		Q:	 <input type="text"  name="Q"/><br/>
		Gain:<input type="text"  name="Gain"/><br/>
		Fc:  <input type="text"  name="Fc"/><br/>
		Type:<input type="text"  name="Type"/><br/>
		En:  <input type="text"  name="En"/><br/>
		no:  <input type="text"  name="no"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm HPF</h1> 
	<h2>ch=4 not have hpf.<h2/>
	<form name="hpf" action="/goform/formHPF" method="post" target="rfFrame">
		Fc:  <input type="text"  name="Fc"/><br/>
		Type:<input type="text"  name="Type"/><br/>
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>
	<!--
	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe>
	<h1>GoForm LPF</h1> 
	<form name="lpf" action="/goform/formLPF" method="post" target="rfFrame">
		Fc:  <input type="text"  name="Fc"/><br/>
		Type:<input type="text"  name="Type"/><br/>
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>
	-->
	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm BPF</h1> 
	<h2>ch=4</h2>
	<form name="bpf" action="/goform/formBPF" method="post" target="rfFrame">
		Fp:  <input type="text"  name="Fp"/><br/>
		Fs:  <input type="text"  name="Fs"/><br/>
		Type:<input type="text"  name="Type"/><br/>
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>
	
	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm limt</h1> 
	<form name="limt" action="/goform/formLIMT" method="post" target="rfFrame">
		T2:  <input type="text"  name="T2"/><br/>
		k2:  <input type="text"  name="k2"/><br/>
		Attack:   <input type="text"  name="Attack"/><br/>
		Release:  <input type="text"  name="Release"/><br/>
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm delay</h1> 
	<form name="dly" action="/goform/formDelay" method="post" target="rfFrame">
		Dly:  <input type="text"  name="Dly"/><br/>
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm vol</h1> 
	<form name="vol" action="/goform/formVol" method="post" target="rfFrame">
		Gain:  <input type="text" name="Gain"/><br/>
		Pol:   <input type="text"  name="Pol"/><br/>
		Mute:  <input type="text"  name="Mute"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		       <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm 3DDelay</h1> 
	<form name="3DDelay" action="/goform/form3DDelay" method="post" target="rfFrame">
		Dly: <input type="text"  name="Dly"/><br/>
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm 3DEn</h1> 
	<h2>ch = 0,1</h2>
	<form name="3DEn" action="/goform/form3DEn" method="post" target="rfFrame">
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm 3DMixer</h1> 
	<form name="3DMixer" action="/goform/form3DMixer" method="post" target="rfFrame">
		-->   :  <input type="text"  name="mix0"/><br/>
		-->dly:  <input type="text"  name="mix1"/><br/>
		-->   :  <input type="text"  name="mix2"/><br/>
		--> x :  <input type="text"  name="mix3"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm SCT HPF</h1> 
	<form name="sctHpf" action="/goform/formSctHpf" method="post" target="rfFrame">
		Fc:  <input type="text"  name="Fc"/><br/>
		Type:<input type="text"  name="Type"/><br/>
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>	

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm SCT VolDepth</h1>  
	<h1>type => 0: hpf,   1: bpf,   2: lpf</h1> 
	<form name="VolDepth" action="/goform/formVolDepth" method="post" target="rfFrame">
		Gain:  <input type="text" name="Gain"/><br/>
		Type:  <input type="text"  name="Type"/><br/>
		Ch:    <input type="text"  name="Ch"/><br/>
		       <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm SCT AGC</h1>  
	<h1>type => 0: hpf,   1: bpf,   2: lpf</h1> 
	<form name="AGC" action="/goform/formAGC" method="post" target="rfFrame">
		T2:  <input type="text"  name="T2"/><br/>
		k2:  <input type="text"  name="k2"/><br/>
		Attack:   <input type="text"  name="Attack"/><br/>
		Release:  <input type="text"  name="Release"/><br/>
		Type:  <input type="text"  name="Type"/><br/>
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		       <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm SCT BPF</h1> 
	<form name="sctBpf" action="/goform/formSctBpf" method="post" target="rfFrame">
		Fp:  <input type="text"  name="Fp"/><br/>
		Fs:  <input type="text"  name="Fs"/><br/>
		Type:<input type="text"  name="Type"/><br/>
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm SCT LPF</h1> 
	<form name="sctLpf" action="/goform/formSctLpf" method="post" target="rfFrame">
		Fc:  <input type="text"  name="Fc"/><br/>
		Type:<input type="text"  name="Type"/><br/>
		En:  <input type="text"  name="En"/><br/>
		Ch:  <input type="text"  name="Ch"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm Sct en & Mixer</h1> 
	<form name="SctMixer" action="/goform/formSctMixer" method="post" target="rfFrame">
		Ch:  <input type="text"  name="Ch"/><br/>
		en   :  <input type="text"  name="en"/><br/>
		-->   :  <input type="text"  name="mix0"/><br/>
		--> hpf :  <input type="text"  name="mix1"/><br/>
		--> bpf :  <input type="text"  name="mix2"/><br/>
		--> lpf :  <input type="text"  name="mix3"/><br/>	
		     <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm analog&digital</h1> 
	<h2>0: analog 1:digital-1, 2: digital-2</h2> 
	<form name="ad" action="/goform/formAD" method="post" target="rfFrame">
		AD:  <input type="text"  name="ad"/><br/>
		mix:  <input type="text"  name="mix"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm outVol</h1> 
	<h2>out = 0,1</h2>
	<form name="ad" action="/goform/formOutVol" method="post" target="rfFrame">
		out:  <input type="text"  name="out"/><br/>
		vol:  <input type="text"  name="vol"/><br/>
		     <input name="" type="submit"/>
	</form>
	<hr/>
	
	<h1>GoForm SigSourSelectOut</h1> 
	<form  action="/goform/formSSEnable" method="post" target="rfFrame">
	1.	<input type=submit value="Enable">
	</form>
	<form  action="/goform/formSSCancel" method="post" target="rfFrame">	
		<input type=submit value="Cancel"><br/>
	</form>
	<h2>type = 0:one,1:loop,2:all</h2>
	<form name="SigSourSelectOut" action="/goform/formSigSourSelectOut" method="post" target="rfFrame">
		in:  <input type="text"  name="in"/><br/>
		out:  <input type="text"  name="out"/><br/>
		total:  <input type="text"  name="total"/><br/>
		type:  <input type="text"  name="type"/><br/>
		2.     <input name="" type="submit"/>
	</form>
	<hr/>
	<!--让表单提交后不刷新页面
	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> 
	<h1>GoForm VuDetect</h1> 
	<form  action="" method="post" target="rfFrame">	
		    <input type="button" value="Vu" onClick="accept1();"/>
	</form>
	<hr/>
	-->

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm VuDetect</h1> 
	<form name="VuDetect" action="/goform/formVuDetect" method="post" target="rfFrame">	
		    <input  name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm save</h1> 
	<form name="save" action="/goform/formSave" method="post" target="rfFrame">	
		name: <input type="text"  name="fileName"/><br/>
		    <input  name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm read</h1> 
	<form name="read" action="/goform/formRead" method="post" target="rfFrame">	
	  name: <input type="text"  name="fileName"/><br/>
		    <input  name="" type="submit"/>
	</form>
	<hr/>

	<iframe style="display: none" id="rfFrame"  name="rfFrame" src="about:blank"></iframe> <!--让表单提交后不刷新页面-->
	<h1>GoForm archive</h1> 
	<form name="archive" action="/goform/formArchive" method="post" target="rfFrame">	
	  name: <input type="text"  name="fileName"/><br/>
		    <input  name="" type="submit"/>
	</form>
	<hr/>
	
</body>
</html>

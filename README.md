<p><strong>Introduction</strong></br>
Hello there.</p>

<p>This is my attempt at writing a RuneScape Classic shell client that uses the mudclient 235 network protocol. This means that, were RuneScape Classic still around, you could technically connect to the live game server with this client. This client is not intended to be a bot, and will not support scripts. This client is intended to merely be a way to play the game in a different manner (hopefully saving your wrist in the process). Ideally, when completed, you will be able to send commands to an 235-compatable RSC server with text commands instead of mouse clicks. The game will probably end up feeling like one of those old text adventure games.</p>

<p>If you're wondering about the name, I picked it to play off the RSC[math operator] naming scheme that a couple other RSC-related projects use. Basically, RSC% is the "remainder" of RSC that you get when you "divide" out the graphics.</p>

<p>I plan on mostly working on this project on my own. Eventually I'll add a open source license once I figure out which one is a good fit for this project so that others can contribute if they want. I also don't plan on using any pre-made libraries (e.g. Boost) because I never learned how to link things and I don't want to learn now.</br>
EDIT: Apparently I'm going to learn how to link things. I forgot about having to work with massive numbers for RSA, and I don't want to have to manage all that manually.</p>

<p><strong>Building</strong></br>
To build this, you will now need Boost. I used 1.82.0, I don't know what other versions will be compatible.</p>

<p>Here's how I did it for Windows:</p>
<ol>
	<li>Download and extract Boost 1.82.0 somewhere on your PC.</li>
	<li>Open a PowerShell or CommandPrompt in the boost_1_82_0 directory.</li>
	<li>Type in <code>.\bootstrap.bat</code> and wait.</li>
	<li>Type in <code>.\b2</code> and wait even more.</li>
	<li>Now go in to Visual Studio, and right-click on the project and go to "Properties."</li>
	<li>Select "VC++ Directories" from the sidebar.</li>
	<li>Add the path to the boost_1_82_0 directory to "Include Directories" (i. e. C:\boost_1_82_0).</li>
	<li>Add the path to the boost_1_82_0\stage\lib directory to the "Library Directories" (i. e. C:\boost_1_82_0\stage\lib).</li>
	<li>Then select "Linker"->"Input" from the sidebar</li>
	<li>Add the following to the Additional Dependencies (I will try to keep this up to date):</br>
	<ul>
		<li>libboost_date_time-vc142-mt-gd-x32-1_82.lib</li>
		<li>libboost_filesystem-vc142-mt-gd-x32-1_82.lib</li>
		<li>libboost_log-vc142-mt-gd-x32-1_82.lib</li>
		<li>libboost_system-vc142-mt-gd-x32-1_82.lib</li>
		<li>libboost_thread-vc142-mt-gd-x32-1_82.lib</li>
	</ul>
	Note: These are the libraries for building Debug x86. If you want to build for Release mode or x64, you'll have to specify those libraries.</li>
</ol>
<p>You should be good to go now.</br>
If you're on Linux or Mac, all I can say is: glhf.</p>

<p>This project is for educational purposes. I don't own RuneScape, nor am I affiliated with Jagex in any way.</p>

<p>Made by <a href="https://github.com/15rtrujillo">Ryan</a>.</p>
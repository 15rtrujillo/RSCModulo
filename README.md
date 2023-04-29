Hello there.

This is my attempt at writing a RuneScape Classic shell client that uses the mudclient 235 network protocol. This means that, were RuneScape Classic still around, you could technically connect to the live game server with this client. This client is not intended to be a bot, and will not support scripts. This client is intended to merely be a way to play the game in a different manner (hopefully saving your wrist in the process). Ideally, when completed, you will be able to send commands to an 235-compatable RSC server with text commands instead of mouse clicks. The game will probably end up feeling like one of those old text adventure games.

If you're wondering about the name, I picked it to play off the RSC[math operator] naming scheme that a couple other RSC-related projects use. Basically, RSC% is the "remainder" of RSC that you get when you "divide" out the graphics.

I plan on mostly working on this project on my own. Eventually I'll add a open source license once I figure out which one is a good fit for this project so that others can contribute if they want. I also don't plan on using any pre-made libraries (e.g. Boost) because I never learned how to link things and I don't want to learn now.
EDIT: Apparently I'm going to learn how to link things. I forgot about having to work with massive numbers for RSA, and I don't want to have to manage all that manually.

<strong>Building</strong>
To build this, you will now need Boost. I used 1.82.0, I don't know what other versions will be compatible.

Here's how I did it for Windows:
<ol>
	<li>Download and extract Boost 1.82.0 somewhere on your PC.</li>
	<li>Open a PowerShell or CommandPrompt in the boost_1_82_0 directory.</li>
	<li>Type in <code>.\bootstrap.bat</code> and wait.</li>
	<li>Type in <code>.\b2</code> and wait even more.</li>
	<li>Now go in to Visual Studio, and right-click on the project and go to "Properties."</li>
	<li>Select "VC++ Directories" from the sidebar.</li>
	<li>Add the path to the boost_1_82_0 directory to "Include Directories" (i. e. C:\boost_1_82_0).</li>
	<li>Add the path to the boost_1_82_0\stage\lib directory to the "Library Directories" (i. e. C:]boost_1_82_0\stage\lib).<\li>
</ol>
You should be good to go now.
If you're on Linux or Mac, all I can say is: glhf.

This project is for educational purposes. I don't own RuneScape, nor am I affiliated with Jagex in any way.

Made by Ryan.
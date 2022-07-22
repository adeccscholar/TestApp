/** \file
\brief   Hauptdatei für die VCL- Anwendung
<hr>
$LastChangedDate: $
$Revision: $
$HeadURL: $
<hr>
\author Volker Hillmann
\date    25.02.2022
\version 1.0
\since   Version 1.0
\copyright Copyright ©2022 adecc Systemhaus GmbH, Alle Rechte vorbehalten.
*/

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <exception>
//---------------------------------------------------------------------------
USEFORM("PersonForm.cpp", frmPerson);
USEFORM("PersonList.cpp", frmPersonList);
USEFORM("FileDlg\FileDlgFormVCL.cpp", frmFileDlg);
USEFORM("MainForm.cpp", frmMain);
USEFORM("DirectoryForm.cpp", frmWorker);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
   catch(std::exception& ex) {
       std::cerr << "Fehler:" << std::endl
                 << ex.what() << std::endl;
      }
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

/** \mainpage Semesterpausenprojekt
Modernes C++ live, ein Problem "build from scratch" mit modernen C++

Ich habe überlegt, ob man alle Anforderungen irgendwie verbinden und an einem konkreten Problem erarbeiten kann. Und wie man das in die semesterfreie Zeit bekommt. Da die meisten ja schon mit C++ zu tun haben, und für alle anderen eine Motivation fürs nächste Semester bekommen können, habe ich mich gegen das komplexere C Beispiel entschieden, und mich für C++ entschieden.

Dabei soll es natürlich um modernes C++ gehen, möglichst unabhängig sein, und sich schrittweise erklären und entwickeln lassen. Oft werden neue Eigenschaften der Standards präsentiert, aber es fehlt die Verbindung zur konkreten Nutzung. Deshalb möchte ich einen anderen Weg suchen und mit einem konkreten Problem beginnen, um dann schrittweise auf Standard C++ und modernes C++ eingehen, die Eigenschaften erklären, und dann mit dem konkreten Problem einsetzen.

Dabei sollen zumindest zwei unterschiedliche IDEs auch live eingesetzt werden. Dabei beginnen wir mit dem C++Builder und der VCL und kommen dann zu Visual Studio und Qt. Für beide Seiten ist es ja auch interessant, mal die anderen Möglichkeiten zu sehen, und dann zu lernen, wie man sich unabhängiger machen kann.
Dabei habe ich mir folgendes vorgenommen, folgende Richtlinien gesetzt:
<ul>
<li> Start ab 21. Februar 2022, Mo / Mi / Fr jeweils ab 20:00 Uhr
<li> vom Problem / konkreter Aufgabe zur Lösung
<li> einfache Aufgabe, Fokus auf dem Lösungsweg, nicht der Aufgabe (Reduktion der Komplexität auf ein notwendiges Maß)
<li> einfache Oberfläche
<li> "build from scratch"
<li> Vorgehensmodelle, Entwurf / Implementierung / Test (Testdaten)
<li> iterativ, vom Problem / Aufgabe zur Erstimplementierung und später Verallgemeinerung
<li> modular und erweiterbar
<li> schrittweise Vorgehensweise und Detailerklärungen, wenn notwendig
<li> öffentlich zugänglich nur über Twitch live + VOD (max. 14 Tage)
<li> keine bereitgestellten Sourcen, alles passiert im Video
<li> offene Diskussion (Chat, Mailing, Discord), Fragen, Ideen
<li> Nutzung von C++11, C++14, C++17 (C++Builder schränkt es ein)
<li> Verwendung von regulären Ausdrücken, Standardcontainern
<li> eingeschränkte Nutzung freier Bibliotheken wie boost und POCO
</ul>
Diskussion über das Projekt im Discord- Server.
*/


/** \page adeccScholar adecc Scholar
adecc Scholar ist ein Projekt, welches sich an alle Studierenden, Lernenden oder
auch bereits Arbeitenden richtet, um ihre Grundkenntnisse in C und C++ aufzufrischen
oder zu erweitern. In den kostenlosen virtuellen Lernveranstaltungen, präsentiert
von Volker Hillmann, wird live programmiert und wir freuen uns über jeden Zuschauer.
Bewusst wurden daher für die Vorlesungen die Studiensemester als Vorlesungszeitraum
gewählt.

Verfolgen können sie die Veranstaltungen auf twitch.tv/volker_adecc (Verlinkung),
auch Feedback oder Fragen sind gerne gesehen, welche sie live im Chat oder auch auf
unserem Discord-Server stellen können
(<a href="https://discord.com/invite/E8tzbu2FTY">Discord Server</a>).

Die erste Vorlesungsreihe "Grundkenntnisse der Programmierung in C/C++" ist bereits
abgeschlossen, aber auf unserem YouTube-Kanal „adecc Scholar“ nachträglich zu
sehen.
(<a href="https://www.youtube.com/channel/UCiDSzuJIAR5vW4akPB0xzEw">Youtube Channel adecc Scholar</a>).

Doch auch außerhalb des Semesters, in der Semesterpause, gibt es was zu lernen.
Ebenfalls komplett kostenlos findet aktuell ein Projekt exklusiv auf Twitch statt,
in dem gezeigt wird, wie mit den Möglichkeiten von modernem C++ die Abhängigkeiten
von Herstellern und  proprietären Bibliotheken aufgelöst werden und Qualität und
Robustheit der eigenen Anwendungen verbessert werden kann. Zu diesem Projekt gibt
es auch erste Feedbacks:

Und ab dem 1. April fängt dann auch schon die nächste Vorlesungsreihe "Einstieg in C++"
mit dem Beginn des Sommersemesters 2022 an.

Außerdem freuen wir uns auf den baldigen Start der adecc Scholar Homepage,
auf der alle News rund um adecc Scholar veröffentlicht werden. Außerdem lassen sich
da alle bisherigen und künftigen Vorlesungen finden.
*/

/**
\dir Semesterpause
\brief Projektverzeichnis für das Projekt
\details Arbeitsverzeichnis mit allen Projektdateien
\see \ref adeccScholar
*/


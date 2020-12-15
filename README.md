# Disk wiper and obfuscator 
A program that overwrites deleted data on a disk. Additionally, obfuscation can be used to confuse an attacker who isn't a computer forensic investigator. This will create fake mp4 files on the deleted space. The program was written in C. Works on Linux and Windows. Tested on Tails (USB), Ubuntu (in a Virtual Box) and on Windows 10. 

You can see how the program works [on Youtube](https://youtu.be/yx7NStpNelw). 

<br><br>

![Reading in text with Synthekst](scr/scr1.jpg?raw=true "Using the program on free space in Ubuntu (Virtual Box)")
<p align="center">Using the program on free space in Ubuntu (Virtual Box).</p>
<br><br>

![Reading in text with Synthekst](scr/scr2.jpg?raw=true "Windows 10 - Overwriting free space on an USB stick")
<p align="center">Windows 10 - Overwriting free space on an USB stick.</p>
<br><br>

*Commands:*

* man  - manual

* quit - exit program

* wipe - wipe deleted files on a disk

  usage:     wipe PATH (-co/-ro) (-wr/-wf) num1 (-r) num2
  
  
  example 1: wipe "/media/amnesia/Lego USB" -co -wr 1
  
  example 2: wipe /media/amnesia/LegoUSB -ro -wf 3
  
  example 2: wipe /media/amnesia/LegoUSB -ro -wf 1 -r 5000
  
  
  PATH    - path to a folder on the disk that should be used for the disk wipe operation.
    
  -co       - clear overwrite (whitespaces in a file)
    
  -ro       - random overwrite (random ASCII characters in a file)
    
  -wr       - write random (filenames are random chars)
    
  -wf       - write filenames (use fake mp4 filenames to obfuscate data)
    
  num1    - number of overwrites (rounds). One round should be enough to overwrite a disk.
    
  num2    - optional: How much space to overwrite. In GB. Per deafult, up to 1 TB will be overwritten. Larger values can be used for larger disks, e.g. 5000 for 5 TB. Smaller values can be used to test the program. (smallest size: 0.1 GB)
    
  -r        - optional: use more random file sizes
  
 <br><br>

![Reading in text with Synthekst](scr/scr3.jpg?raw=true "Tails Linux - Using disk wipe on an USB stick")
<p align="center">Tails Linux - Using disk wipe on an USB stick.</p>
<br><br>

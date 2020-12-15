# Disk wiper and obfuscator 
A program that overwrites deleted data on a disk. Additionally, obfuscation can be used to confuse an attacker who isn't a computer forensic investigator. This will create fake mp4 files on the deleted space. Written in C. Works on Linux and Windows. Tested on Tails (USB), Ubuntu (Virtual Box) and Windows 10. 

You can see how the program works [on Youtube](https://youtu.be/yx7NStpNelw). 


* man  - manual

* quit - exit program

* wipe - wipe deleted files on a disk

  usage:     wipe PATH (-co/-ro) (-wr/-wf) num1 (-r) num2
  
  
  example 1: wipe "/media/amnesia/Lego USB" -co -wr 1
  
  example 2: wipe /media/amnesia/LegoUSB -ro -wf 3
  
  example 2: wipe /media/amnesia/LegoUSB -ro -wf 1 -r 5000
  
  
  PATH    - path to a folder on the disk that should be used for the disk wipe operation.
    
  -co       - clear overwrite (whitespaces in a file)
    
  -ro       - random overwrite (random ascii characters in a file)
    
  -wr       - write random (filenames are random)
    
  -wf       - write filenames (use fake filenames [obfuscate data])
    
  num1    - number of overwrites (rounds)
    
  num2    - optional: How much space to overwrite. In GB. Per deafult, up to 1 TB will be overwritten. (smallest size: 0.1 GB)
    
  -r        - optional: use more random file sizes

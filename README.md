# mbr-fat32-adventures
Scratchpad repo used to learn the inner workings of MBR & FAT32/16

## Links
Ressources I used to read this pile of shit
 - https://en.wikipedia.org/wiki/Master_boot_record
 - https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system
 - https://www.cs.fsu.edu/~cop4610t/lectures/project3/Week11/Slides_week11.pdf
 - https://www.cs.fsu.edu/~cop4610t/assignments/project3/spec/fatspec.pdf
 - https://www.pjrc.com/tech/8051/ide/fat32.html
 - https://cscie92.dce.harvard.edu/spring2021/slides/FAT32%20File%20Structure.pdf
 - (Probably forgot some)
 
## Current state of things:
#### MBR:
 - ✅ Read MBR boot sector
#### Bios parameter block:
 - ✅ Read DOS2.0 bios parameter block
 - ✅ Read DOS3.31 bios parameter block
 - ✅ Read Extended bios parameter block
 - ✅ Read FAT32 Extended bios parameter block
#### FAT32 partition:
 - ✅ Read FAT32 boot sector
 - ✅ Read FAT32 information sector
 - ✅ Read FAT32 FAT table(s)
 - ✅ Read entries in FAT32 Root directory cluster with LFNs handling
 - ❌ Read all directories in FAT32 part (shouldn't be complicated)
 - ❌ Read files in FAT32 part (shouldn't be complicated)
#### FAT16 partition:
 - ✅ Read FAT16 boot sector
 - ❌ Read FAT16 FAT table(s)
 - ❌ Read entries in FAT32 Root directory cluster with LFNs handling
 - ❌ Read all directories in FAT16 part
 - ❌ Read files in FAT16 part
#### Extended partition:
 - ❌ Read MBR extended partition

![result_example](https://user-images.githubusercontent.com/17061996/179110745-35a54265-ed90-4fb0-bd94-65456be36dbd.png)
 
## Usage:
Need a file named "file" representing a disk image with one primary fat32 partition and multiple extended fat32 partitions

![image](https://user-images.githubusercontent.com/17061996/178532228-cea01d02-24ca-40b8-9aae-7c467eaf07a1.png)

## Commands
```bash
# Mount file to partitionned loop:
sudo losetup -P /dev/loop18 file
# Detach loop
sudo losetup -d /dev/loop18

# Create filesystem
sudo mkfs.fat /dev/loop18p1 -n PART1
sudo mkfs.fat /dev/loop18p5 -n PART5
sudo mkfs.fat /dev/loop18p6 -n PART6
sudo mkfs.fat /dev/loop18p7 -n PART7
sudo mkfs.fat /dev/loop18p8 -n PART8
sudo mkfs.fat /dev/loop18p9 -n PART9
sudo mkfs.fat /dev/loop18p10 -n PART10
sudo mkfs.fat /dev/loop18p11 -n PART11
sudo mkfs.fat /dev/loop18p12 -n PART12
sudo mkfs.fat /dev/loop18p13 -n PART13
sudo mkfs.fat /dev/loop18p14 -n PART14
```


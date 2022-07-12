# mbr-fat32-adventures
Scratchpad repo used to learn the inner workings of MBR &amp; FAT 32

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

## Links
https://en.wikipedia.org/wiki/Master_boot_record

https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system

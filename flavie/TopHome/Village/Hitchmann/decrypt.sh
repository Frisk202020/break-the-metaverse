echo file to decrypt ?

read filename

gpg -o $filename --decrypt --pinentry-mode=loopback $filename.gpg


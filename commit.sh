#a script to submit the code of project
#param $1 the name of the code file or directory
#author ygh
#data 2017.6.3
git add $1 &&
git commit -m "commit" &&
git push -u origin master 


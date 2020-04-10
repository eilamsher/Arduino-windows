## Arduino Windows

### Requirements 
*you know, things that are required..*
- [git](https://git-scm.com/downloads)
- [arduino ide](https://www.arduino.cc/en/main/software)

### Getting Started 
*so how do i start this shit?*
- open teminal
- cd to your desired destination
- run `git clone git@github.com:shgoren/deviceName-01.git` 

### Development 
*i have local changes, how do i push them?*
#### Never commit\push changes to master
- `git branch` to check current branch
- `git branch {NAME}` to create a local branch with {NAME}
- ` git push --set-upstream origin {NAME}` to create a remote branch with name
- `git checkout {NAME}` to move to the newly created branch
#### Before you code
- run `git pull origin master` to get the latest updates
#### After you code
- `git pull origin master` to get the most recent changes to your branch
	- fix conflict if arise (git will notify you)
- `git commit -am "message here"` to commit changes on local branch 
- `git push` to publish your changes

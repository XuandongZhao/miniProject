music_radio_driver is the top module.
Get music( .mp3), lyrics(.lrc), picture(.jpg) from Baidu online music radio. 
It is already sufficient to your use.

Note: the download folder is the folder where your Qt buiding your project
rather than the folder where your codes are.


How it works: 

First: 
initialize the menu:
ChannelsWidget::ChannelsWidget(QWidget *parent, QNetworkCookieJar *cookJar)
using the constructor

Second:
when button in channelswidget.ui (channel menu) is clicked:
void ChannelsWidget::channelSelected(int iChannel)
is called.

Then: 
in class music_radio_driver:
void music_radio_driver::channelChangedSlot(CHANNEL_INFO channel)
is called as a  slot function.

download procedure begins:
void music_radio_driver::initSongIdList()
void music_radio_driver::DownloadSongs_InTheList(int BeginIndex, int EndIndex)//play(int index)

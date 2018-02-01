// VictorCode/
/*
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

*/
#include "music_radio_driver.h"
#include "getsongplaylistid.h"
#include "downloadfile.h"
#include "getsongreallink.h"
#include "getlrc.h"
#include "getaristpic.h"
#include "list.h"
#include <QDir>
#include <QMessageBox>
const int MAX_SONG_NUM =1;
const QDir dir;
const QString ONLINE_RADIO_DOWNLOAD_DIR = dir.currentPath() + "/OnlineRadioDownloadDir";

music_radio_driver::music_radio_driver()
{
    //victor code added below:
    m_cookJar = new QNetworkCookieJar;
    m_channelWidget = new ChannelsWidget(0, m_cookJar);

    /*
     * class channelwidget :
signals:
    void channelChanged(CHANNEL_INFO Channel);
*/
    QObject::connect(m_channelWidget, SIGNAL(channelChanged(CHANNEL_INFO)), this, SLOT(channelChangedSlot(CHANNEL_INFO)));
    /*
  connect(this, SIGNAL(channelInfoSignal(QString)), ui->aristPicWidget, SLOT(channelChangedSlot(QString)));

*/
}

void music_radio_driver::ShowChannelMenu(void){
    m_channelWidget->show();//show ui
}



void music_radio_driver::channelChangedSlot(CHANNEL_INFO channel)
{
    m_songIdList.clear();//local: QList <QString> m_songIdList;
    m_iCurrentSongIndex = 0;//int

//CHANNEL_INFO m_currentChannelId;//only a tiny struct
    m_currentChannelId.channelId = channel.channelId;
    m_currentChannelId.channelName = channel.channelName;

    //初始化某个频道列表下的所有歌曲
    initSongIdList();
}

//
void music_radio_driver::initSongIdList()
{
    //第二步,获取某个频道下的歌曲ID列表
    GetSongPlayListId getPlayListId(this, m_cookJar);//need #include "VictorCode/getsongplaylistid.h"
    m_songIdList = getPlayListId.getSongIdList(m_currentChannelId.channelId);//local: QList <QString> m_songIdList;
    qDebug() << "频道:" << m_currentChannelId.channelName << m_currentChannelId.channelId<< "共有歌曲" << m_songIdList.size();
    QMessageBox::about(NULL, "About", "About this <font color='red'>application</font>");

    QString info = m_currentChannelId.channelName + " 共有歌曲: " + QString::number(m_songIdList.size());
    qDebug() << info;
    DownloadSongs_InTheList(0,MAX_SONG_NUM);
    //emit channelInfoSignal(info);
/* to emit channelInfoSignal(info);
 * following is needed:
Artist Picture:
#include "aristpicture.h"
    connect(this, SIGNAL(channelInfoSignal(QString)), ui->aristPicWidget, SLOT(channelChangedSlot(QString)));

*/
    //play(0);


}

// new line shown below

void music_radio_driver::DownloadSongs_InTheList(int BeginIndex, int EndIndex)//play(int index)
{
    for(int index=BeginIndex;index <= m_songIdList.size() &&index <= EndIndex;index++ ){
        GetSongRealLink getSongLink;//the web link getter
        m_currentSongInfo = getSongLink.getSongRealLinkById(m_songIdList.at(index));

        //begin the download:
        QString fileName;
        DownLoadFile downMp3;//need #include "downloadfile.h"

        QDir dir;
        if(!dir.exists(ONLINE_RADIO_DOWNLOAD_DIR))
        {
            dir.mkdir(ONLINE_RADIO_DOWNLOAD_DIR);
        }
        fileName = ONLINE_RADIO_DOWNLOAD_DIR + "/" + m_currentSongInfo.songName + ".mp3";//need: SONG_INFO m_currentSongInfo;

    /*another tiny structure: SONG_INFO m_currentSongInfo in "getsongreallink.h"
    typedef struct _SONG_INFO
    {
        QString songRealLink;
        QString songName;
        QString artistName;
        QString songPicSmall;
        QString songPicRadio;
        QString time;
        QString albumName;
        QString lrcLink;
        QString size;
    }SONG_INFO;
    */

        qDebug() << fileName;

        downMp3.getMp3File(fileName, m_currentSongInfo.songRealLink);

        qDebug() << "下载完成" + fileName;

        ////////////////////
        //

        //获取歌词
        fileName = ONLINE_RADIO_DOWNLOAD_DIR + "/" + m_currentSongInfo.songName + ".lrc";
        GetLrc getLrc;
        QString lrc = getLrc.getLrc(m_currentSongInfo.lrcLink);
        //ui->lycWidget->currentSongChannged(m_currentSongInfo.songName, m_currentSongInfo.artistName, m_currentSongInfo.albumName);
        //ui->lycWidget->setLrc(lrc);
        qDebug() << lrc;
        //write procedure
        QFile file(fileName);
            if (file.open(QIODevice::ReadWrite)) {
                QTextStream stream(&file);
                stream << lrc << endl;
            }



        //歌手图片
        fileName = ONLINE_RADIO_DOWNLOAD_DIR + "/" + m_currentSongInfo.songName + ".jpg";
        GetAristPic getPic;
        QPixmap picMap = getPic.getAristPic(m_currentSongInfo.songPicRadio);
        picMap.save(fileName,"JPG");
                //ui->aristPicWidget->setAristPic(picMap);
    }


    /*another tiny structure: SONG_INFO m_currentSongInfo in "getsongreallink.h"
    typedef struct _SONG_INFO
    {
        QString songRealLink;
        QString songName;
        QString artistName;
        QString songPicSmall;
        QString songPicRadio;
        QString time;
        QString albumName;
        QString lrcLink;
        QString size;
    }SONG_INFO;
    */

    /*
     *     if(index > m_songIdList.size())
        return;

    // play the music, call fucntion
    m_pPlayer->setMedia(QUrl(m_currentSongInfo.songRealLink));
    m_pPlayer->play();
*/
/*
    //获取歌词
    GetLrc getLrc;
    QString lrc = getLrc.getLrc(m_currentSongInfo.lrcLink);
    ui->lycWidget->currentSongChannged(m_currentSongInfo.songName, m_currentSongInfo.artistName, m_currentSongInfo.albumName);
    ui->lycWidget->setLrc(lrc);

    //显示歌手图片
    GetAristPic getPic;
    QPixmap picMap = getPic.getAristPic(m_currentSongInfo.songPicRadio);
    ui->aristPicWidget->setAristPic(picMap);
    */
}

/*
//下载歌曲, automatically
void music_radio_driver::downloadtoolButton_clicked()
{
    QString fileName;
    DownLoadFile downMp3;//need #include "downloadfile.h"

    QDir dir;
    if(!dir.exists("./download"))
    {
        dir.mkdir("./download");
    }
    fileName = "./download/" + m_currentSongInfo.songName + ".mp3";//need: SONG_INFO m_currentSongInfo;




    qDebug() << fileName;

    downMp3.getMp3File(fileName, m_currentSongInfo.songRealLink);

    qDebug() << "下载完成";
}
*/

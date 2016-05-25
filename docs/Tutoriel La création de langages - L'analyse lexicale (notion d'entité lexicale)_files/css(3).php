/**
 * Theme Name: Metro
 * Version: 1.0
 * Author: Pixel Goose Studio
 * Author URL: http://pixelgoose.com/
 * Copyright (c) 2012 Pixel Goose Studio.  All rights reserved.
 * http://pixelgoose.com/
 */


ol#forums > li:first-child .forumhead {
	margin-top: 0;
}
.forumbit_nopost .forumrowdata {
	border-left: 1px solid #e4e4e4;
	border-right: 1px solid #e4e4e4;
	border-bottom: 1px solid #e4e4e4;
}
.forumbit_nopost .forumhead h2, .forumbit_post .forumhead h2 {
	overflow: hidden;
	border-left: solid 1px #43A6DF;
	border-right: solid 1px #43A6DF;
	width: 100%;
	background-color: #43A6DF;
}
.forumbit_nopost .forumhead span.forumlastpost, .forumbit_post .forumhead span.forumlastpost {
	font-size: 12px;
}
.forumbit_post .foruminfo .forumdata .forumtitle a, .forumbit_nopost .forumbit_nopost .forumrow .forumtitle a {
	color: #2E3539;
}
.forumbits .forumhead {
	border-left: 1px solid #43A6DF;
	border-right: 1px solid #43A6DF;
}
.lastpostby {
	margin-bottom: 6px;
}
.forumbit_post .forumlastpost .lastpostdate {
	color: #797979;
}
.forumstats-inline {
	margin-bottom: 12px;
}
.forumstats-inline li {
	display: inline;
}
.wgo_block h2.blockhead {

	padding: 14px 0 14px 12px;


}
.memberaction_body.popupbody li .siteicon_profile:hover {
	background-image: url(images/metro/blue/site_icons/profile-light.png);
}
.memberaction_body.popupbody li .siteicon_forum:hover {
	background-image: url(images/metro/blue/site_icons/forum-light.png);
}
.memberaction_body.popupbody li .siteicon_homepage:hover {
	background-image: url(images/metro/blue/site_icons/homepage-light.png);
}
.memberaction_body.popupbody li .siteicon_message:hover {
	background-image: url(images/metro/blue/site_icons/message-light.png);
}
.memberaction_body.popupbody li .siteicon_blog:hover {
	background-image: url(images/metro/blue/site_icons/blog-light.png);
}
.memberaction_body.popupbody li .siteicon_article:hover {
	background-image: url(images/metro/blue/site_icons/article-light.png);
}
#top_header {
	height: 36px;
	padding-top: 12px;
}
#top_header .globalsearch {
	border: solid 1px #e4e4e4;
	/*background-attachment: scroll;
	background-image: url(images/metro/blue/misc/header-search-bg.png);
	background-repeat: no-repeat;
	background-position: left top;*/
	background-color: #ffffff; 
	height: 30px;
}
#top_header .globalsearch .searchbutton {
	background-attachment: scroll;
	background-image: url(images/metro/blue/misc/search-button-bg.png);
	background-repeat: no-repeat;
	background-position: left 0;
}
#top_header .globalsearch .searchbutton:hover {
	background-attachment: scroll;
	background-image: url(images/metro/blue/misc/search-button-bg.png);
	background-repeat: no-repeat;
	background-position: left -26px;
}
.welcomelink img {
	max-width: 24px;
}
.notifications-number {
	background-color: #FF7F00;
	border-radius: 20px 20px 20px 20px;
	color: #FFFFFF;
	font-size: 10px;
	padding: 2px 6px;
}
#middle_header {
	height: 166px;
	background-color: #43A6DF;
	position: relative;
}
.navtabs ul.floatcontainer {
	border-top: solid 12px #f6f6f6;
	background-color: #2E3539;
	height: 34px;
	font-size: 13px;
	font-family: 'Open Sans', sans-serif;
}
.navtabs ul.floatcontainer > li:last-child {
	margin-right: 12px;
}
.navtabs ul.floatcontainer .popupbody li:last-child {
	/*margin-right: 0px;*/
}
.navtabs li a.navtab {
	text-transform: lowercase;
	line-height: 23px;
}
.navtabs > li {
    border-left: 12px solid #f6f6f6;
}
.navtabs li .popupmenu li {
    display: inline;
}
.navtabs li a.navtab,
.navtabs ul.floatcontainer .popupbody li a,
.isuser .popupbody li a,
.lastpostby .popupbody li a,
.toolsmenu .popupbody li a,
.popupbody li label,
.popupbody li a,
dl.tabslight dd a,
#profile_tabs dl.tabslight dd.userprof_moduleinactive, dl.as-tabs dd,
#whatsnewsidebar div.blocksubhead.smaller li a {
	-webkit-transition: all 0.3s ease;
	-moz-transition: all 0.3s ease;
	-ms-transition: all 0.3s ease;
        -o-transition: all 0.3s ease;
	transition: all 0.3s ease;
}
.navtabs ul.floatcontainer .popupbody li a {
	line-height: 40px;
}
#navtabs > li > a {
	background-attachment: scroll;
	background-image: url(images/metro/blue/misc/nav-icons-bg.png);
	background-position: left -514px; 
	background-repeat: no-repeat;
	/*background-color: #43A6DF;*/

}
#vbtab_whatsnew > a {
	background-position: left 0 !important; 
}
#vbtab_cms > a {
	background-position: left -128px !important; 
}
#vbtab_forum > a {
	background-position: left -256px !important; 
}
#vbtab_blog > a {
	background-position: left -384px !important; 
}
.navtabs .floatcontainer .popupmenu > .popupbody {
	top: 46px !important;

}
.navtabs .floatcontainer .popupmenu > .popupbody,
.toplinks ul.isuser .notifications .popupbody,
.toolsmenu .popupbody,
.forumfoot .popupmenu .popupbody,
.pagination .popupbody,
.postlist .postlistfoot .popupbody,
.posts .reputationpopupmenu .popupbody,
.blockfootpad .popupbody,
.popupbody,
.tborder.vB_DatePicker.page {
	-moz-box-shadow: 0px 4px 7px rgba(0, 0, 0, 0.3);
	-webkit-box-shadow: 0px 4px 7px rgba(0, 0, 0, 0.3);
	box-shadow: 0px 4px 7px rgba(0, 0, 0, 0.3);
}
.pagination .popupbody li > a:hover, .pagination .popupbody li > label:hover {
	color: #3E3E3E;
}
.isuser li .popupbody li a {
	font-size: 13px;
	text-transform: none;
}
.isuser > li a#fb_loginbtn{
    padding-top: 6px !important;
}

/* popup login */

#mask {
	display: none;
	background: #000; 
	position: fixed; left: 0; top: 0; 
	z-index: 10;
	width: 100%; height: 100%;
	opacity: 0.6;
	z-index: 999;
}

.login-popup {
	display:none;
	width: 364px;
	background: #fff;
	padding: 32px 0 16px; 	
	float: left;
	font-size: 1.2em;
	position: fixed;
	top: 50%; left: 50%;
	z-index: 99999;
	box-shadow: 0px 0px 20px #434343; /* CSS3 */
	-moz-box-shadow: 0px 0px 20px #434343; /* Firefox */
	-webkit-box-shadow: 0px 0px 20px #434343; /* Safari, Chrome */
}
#navbar_username,
#navbar_password_hint,
#navbar_password {
	width: 254px;
	padding: 0 12px 0 32px;
	border: solid 1px #ebebeb;
	height: 40px;
	line-height: 40px;
	background-attachment: scroll;
	background-image: url(images/metro/blue/misc/login-icons.png);
	background-repeat: no-repeat;
}
#navbar_username {
	background-position: 12px 0;
}

#navbar_password_hint,
#navbar_password {
	background-position: 12px -40px;
}
.navbar_username_outer,
.navbar_password_outer {
	padding: 12px 32px;
}
.navbar_username_outer.active,
.navbar_password_outer.active {
	padding: 12px 32px 12px 26px;
	background-color: #f2f2f2;
	border-left: solid 6px #43A6DF;
}

.loginbutton {
	background-color: #43A6DF;
	color: #fff;
	font-size: 11px;
	font-weight: bold;
	-webkit-box-shadow:  0px 0px 0px 3px #d8d8d8;
	box-shadow:  0px 0px 0px 3px #d8d8d8;
	border: none;
	padding: 6px;
	cursor: pointer;
}
.login-ctrl {
	padding: 12px 32px 6px;
	font-size: 11px;
	overflow: hidden;
}
.login-ctrl .remember {
	float: left;
	margin-top: 6px;
}
.login-ctrl .loginbutton {
	float: right;
}
.register-ctrl {
	margin: 12px 32px 12px;
	padding-top: 12px;
	border-top: solid 1px #ebebeb;
}
.login-popup-fb {
	float: right;
}
img.close-button { 
	float: right; 
	margin: -26px 6px 0 0;
}
#login-text {
	font: 24px 'Open Sans',sans-serif;
	color: #43A6DF;
	text-transform: lowercase;
	padding: 0 32px;
	margin-bottom: 12px;
}
.login-popup fieldset { 
	border:none; 
}


.notices li {
	padding: 10px 10px 10px 56px;
	background-attachment: scroll;
	background-image: url(images/metro/blue/misc/notice-exclamation.png);
	background-repeat: no-repeat;
	background-position: 10px 10px;
	min-height: 36px;
}


.newcontent_textcontrol > span,
.pagetitleinfo.textcontrol > span {
	float: right;
	height: 32px;
	width: 32px;
	text-indent: -9999px;
	background-color: #43A6DF;
	margin-left: 12px;
	background-attachment: scroll;
	background-image: url(images/metro/blue/buttons/new-content-plus.png);
	background-repeat: no-repeat;
	background-position: center center;  
	text-align: left;
}
.newcontent_textcontrol > span.closed-thread {
	background-image: url(images/metro/blue/buttons/locked-content.png);
}
.postlist .reputationpopupmenu .blockhead {
	padding: 14px 12px;
}
.postlist .reputationpopupmenu h3.blockhead {
	font-size: 14px;
}
.thread_info_block {
	margin-bottom: 12px;
}
#social_bookmarks_list {
	padding-top: 12px;
}
#usercp_nav li:last-child h4 {
	border-bottom: none;
}

.blockhead-checkbox {
	float: right;
	padding-top: 8px;
}
.blocksubhead.sortrow {
	margin-bottom: -1px;
}
.threadlisthead.table {
	padding: 2px 0;
}
.postbit.postbit-lite {
	border: 1px solid #E4E4E4 !important;
	padding: 12px;
	margin-bottom: 12px;
	-moz-box-sizing: border-box;
	box-sizing: border-box;
        -webkit-box-sizing: border-box;
}
.postbit-lite .avatarlink {
	margin-right: 12px;
}
.postlist_moderation .blockbody,
.group-moderation .blockbody,
.attachment_moderation .blockbody {
	border-left: 1px solid #E4E4E4;
	border-right: 1px solid #E4E4E4;
	border-bottom: 1px solid #E4E4E4;
}
.threadbit .discussionrow .inner {
	float: none !important;
}
.group-moderation .threadbit .discussionrow {
	margin: 0;
}
.group-moderation .threadlisthead .threadimod {
	right: 10px;
}
.postbitfoot.floatcontainer .postcontrols {
	display: block;
	margin-top: 12px;
}
#calendar_content .eventcontrols .textcontrol {
	background-color: transparent;
}
#calendar_content .eventcontrols a.textcontrol:hover {
	color: #43A6DF !important;
}
.calendar th.blocksubhead:first-child {
	border-left: solid 1px #e4e4e4;
}
.calendar th.blocksubhead:last-child {
	border-right: solid 1px #e4e4e4;
}
#mygroups h2.blockhead {
	background-attachment: scroll;
	background-image: url(images/metro/blue/site_icons/network-light.png);
	background-repeat: no-repeat;
	background-position: 12px center; 
	padding-left: 32px;
	border-top: 1px solid #2E3539 !important;
	border: none;
}
#recentgroups h2.blockhead {
	background-attachment: scroll;
	background-image: url(images/metro/blue/buttons/star-light.png);
	background-repeat: no-repeat;
	background-position: 12px center; 
	padding-left: 32px;
	border-top: 1px solid #2E3539 !important;
	border: none;
}
#mygroups h2.blockhead img,
#recentgroups h2.blockhead img {
	display: none;
}

#newgroups {
	margin-top: -12px;
}
#mygroups h2.blockhead, #recentgroups h2.blockhead, #pictures h2.blockhead,
#group_discussion_inlinemod_form .blockhead h2, #albumlist h2.blockhead,
#delete_form h2.blockhead, #edit_form h2.blockhead,
#memberlist h2.blockhead, h2.blockhead {
	font-size: 14px;
	font-weight: normal;
}
.blocksubheadinfo, .blockheadinfo {
	font-size: 12px;
	color: #ffffff !important;
}
#w_categories li {
    padding: 6px 12px;
}
#groupsearch .searchimg {
	width: 26px;
	height: 26px;
	background-attachment: scroll;
	background-image: url(images/metro/blue/misc/search-button-bg.png);
	background-repeat: no-repeat;
	background-position: left 0;
	border: 0;
	cursor: pointer;
	float: right;
	text-indent: -9999px;
}
#groupsearch .searchimg:hover {
	width: 26px;
	height: 26px;
	background-attachment: scroll;
	background-image: url(images/metro/blue/misc/search-button-bg.png);
	background-repeat: no-repeat;
	background-position: left -26px;
}
#groupsearch input.searchbox {
	border: none;
	font-size: 14px;
	height: 22px;
	width: 218px;
	padding: 1px;
}
.grouplist .textcontrol, #newgroups .textcontrol {
	color: #424242;
}
.grouplist .textcontrol:hover, #newgroups .textcontrol:hover {
	color: #424242;
}
#groupinfo dt {
	font-weight: normal;
}
#groupstats .stats {
	border-bottom: 1px solid #E4E4E4;
	padding: 6px 0;
}
#groupstats .stats:last-child {
	border-bottom: none;
}
.standard_error .blocksubhead {
	border-left: 1px solid #E4E4E4;
	border-right: 1px solid #E4E4E4;
}
#albumlist .blockbody.floatcontainer {
	border: 1px solid #E4E4E4;
	border-top: none !important;
	padding-bottom: 12px;
}
.block#album {
	padding: 12px;
	border: solid 1px #E4E4E4;
	background-color: #ffffff;
}
.blockbody.albumedit {
	background-color: transparent;
}
#memberlist_table {
	border: solid 1px #E4E4E4;
	border-top: none !important;
}
#memberlist_search .popupbody li input.searchbox {
	padding: 3px 0;
}
.toolsmenu#grouppagetitle ul {
	margin: 12px;
}
.blockbody > .groupbit {
	border-left: solid 1px #E4E4E4;
	border-right: solid 1px #E4E4E4;
}
.blockbody > .groupbit:last-child {
	border-bottom: solid 1px #E4E4E4;
}
.activitystream .blockbody {
	background-color: transparent;
}
.eventhead .eventdate,
.eventbit .username_container,
.eventbit .eventuseravatar {
	padding-left: 12px;
}
h2.searchlisthead {
	/*margin-bottom: 12px;*/
}
#usercp_content dl.stats {
	line-height: 48px;
	padding: 0 12px 0;
}
#pmfolderlist dl.stats {
	line-height: 16px;
	padding: 6px 12px 0;
}
#userinfoblock {
	border: solid 1px #E4E4E4;
	border-top: none !important;
	background-color: #ffffff;
	padding-bottom: 12px;
}
#sidebar_container h1.blocksubhead {
	height: 48px !important;
	padding: 0 !important;
}
.blocksubhead.prof_blocksubhead > span {
	line-height: 48px;
	padding-left: 12px;
}
#sidebar_container h1.blocksubhead .textcontrol img {
	top: 14px;
	padding-right: 12px;
}
#sidebar_container .usertitle {
	color: #2E3539;
}
#sidebar_container .userranks {
	text-align: center;
	margin-bottom: 12px;
}
#sidebar_container .mini_stats .stats {
	border-bottom: 1px solid #E4E4E4;
	padding: 6px 0;
}
#sidebar_container .mini_stats .stats:last-child {
	border-bottom: none;
}
.member_blockrow dt {
	font-weight: normal;
	color: #777777 !important;
}
#sidebar_container h5.blocksubhead.smaller {
	height: 48px;
	line-height: 48px;
	font-size: 14px !important;
	padding: 0 12px !important;
}
#sidebar_container h5.blocksubhead.smaller a {
	color: #ffffff;
}
#sidebar_container h5.blocksubhead.smaller .textcontrol {
	padding-top: 15px;
}
#sidebar_container #blog_sidebar_generic h5.blocksubhead, #sidebar_container #blog_sidebar_generic h4.blocksubhead.smaller, .blog #sidebar_container h2.blocksubhead.smaller, .blog #moveable_blocks .blocksubhead,
.blog #blog_user_sidebar .blocksubhead {
	height: 48px;
	line-height: 48px;
	font-size: 14px !important;
	padding: 0 12px !important;
	background-color: #2E3539;
	margin: -12px -12px 12px;
	font-weight: normal;
}
#sidebar_container #blog_sidebar_generic h5.blocksubhead .collapse, #sidebar_container h4.blocksubhead.smaller .collapse, .blog #moveable_blocks .blocksubhead .collapse  {
	margin-top: 15px;
}
#profile_tabs dl.tabslight dd {
	margin-right: 1px;

}
#profile_tabs dl.tabslight dd.userprof_moduleinactive {
	background-color: #43A6DF;
	border-color: #43A6DF;
}
#profile_tabs dl.tabslight dd.userprof_moduleinactive:hover {
	background-color: #2E3539;
	border-color: #2E3539;
}
dl.as-tabs dd {
	background-color: #43A6DF;
	border-color: #43A6DF;
}
dl.as-tabs dd:hover {
	background-color: #2E3539;
	border-color: #2E3539;
}

dl.as-tabs dd#asuser a:hover, dl.as-tabs dd.selected#asuser a {
    background-image: url(images/metro/blue/site_icons/profile-light.png);
}
dl.as-tabs dd#asfriend a:hover, dl.as-tabs dd.selected#asfriend a {
    background-image: url(images/metro/blue/site_icons/network-light.png);
}
dl.as-tabs dd#assub a:hover, dl.as-tabs dd.selected#assub a {
    background-image: url(images/metro/blue/site_icons/subscribe-light.png);
}
dl.as-tabs dd#asphoto a:hover, dl.as-tabs dd.selected#asphoto a {
    background-image: url(images/metro/blue/site_icons/photo-light.png);
}
.block.userprof_editor,
.postbit-lite.postcontainer.userprof,
.postbit-lite.deleted.userprof {
	background-color: #ffffff;
}
.member_blockrow.userprof_headers.userprof_headers_border  {
	background-color: #f2f2f2;
}
.blocksubhead.subsectionhead.userprof_headers.userprof_headers_border {
	background-color: #f2f2f2;
	border-top: solid 1px #e4e4e4;
	border-bottom: solid 1px #e4e4e4;
	border-left: none;
	border-right: none;
}
.blocksubhead.subsectionhead.userprof_headers.userprof_headers_border:first-child {
	/*border-top: none;*/
}
#view-aboutme {
	border: solid 1px #e4e4e4;
}
#view-aboutme dl.blockrow dt {
	font-weight: normal;
}
.friends_list .userprof_content_border {
	border: solid 1px #e4e4e4;
}
#view-blog .blogentrybit .userprof_content {
	padding: 12px;
	border: solid 1px #e4e4e4;
}
#view-blog div.blocksubhead {
	border: none;
	padding: 0;
	background-color: transparent;
	margin-top: 12px;
}
#view-blog .bloglisthead dd {
	border-top: solid 1px #e4e4e4;
	border-bottom: solid 1px #e4e4e4;
}
#view-blog .bloglisthead dt + dd {
	border-left: solid 1px #e4e4e4;
}
#view-blog .bloglisthead dd:last-child {
	border-right: solid 1px #e4e4e4;
}
.blog .bloglist li .wrapper {
	padding: 12px 12px 0 12px;
}
.blog #pagetitle .popupgroup {
	margin-top: 10px;
}

.bloghead {
	color: #797979;
}
#whatsnewsidebar {
	border: solid 1px #e4e4e4;
}
#whatsnewsidebar .blockbody {
	border-top: solid 3px #2E3539 !important;
	border: none;
}
#whatsnewsidebar div.blocksubhead.smaller li a:hover {
	text-decoration: none;
	background-color: #2E3539;
}
#blog_sidebar_generic .formcontrols {
	border: none;
}
#blog_sidebar_generic .blockrow {
	padding: 6px;
}
#c_blog_calendar {
	margin: 0 -12px;
}
#c_blog_calendar th {
	font-size: 14px;
	font-weight: normal;
}
#blog_user_sidebar #userinfoblock {
	border-width: 0 0 1px 0;
}
#blog_user_sidebar .stats {
	font-size: 13px;
	margin-bottom: 6px;
}
.blog .bloglistall .columnsort {
	border-left: solid 1px #e4e4e4;
	border-right: solid 1px #e4e4e4;
}
dl.blogcatbit, tr.blogcatbit {
	border-left: solid 1px #e4e4e4;
	border-right: solid 1px #e4e4e4;
	border-bottom: solid 1px #e4e4e4;
	border-top: none;
}
.blogsidebarorganize, .blogcustompages, .bloglist.table {
	background-color: #ffffff;
}
.member-blogs, .bloglist.blogsidebarorganize, .bloglist.blogcustompages, .blog-members, .blogsubscriptions, .blogentrysubscriptions {
	border: solid 1px #e4e4e4;
	border-top: none;
}
.bloglist.blogsidebarorganize {
	margin-left: -1px;
}
.bloglist.table {
	/*border-top: solid 1px #e4e4e4 !important;*/
}

#usercss_form .blockbody.formcontrols, .edit-desc, .organize-sidebar, .blog-permissions {
	border-top: solid 1px #e4e4e4 !important;
}
.blog-stats {
	border: solid 1px #e4e4e4;
}
.blog-stats dl dd.td {
	padding: 6px 12px;
}
.bloggroupslist {
	border-left: solid 1px #e4e4e4;
	border-right: solid 1px #e4e4e4;
}
.blog-members {
	margin-right: -2px !important;
}
.bloglistinfo.blocksubhead {
	border-left: 1px solid #E4E4E4;
}
.blocksubhead.blogcatblogentries {
	border-right: 1px solid #E4E4E4;
}
.blog-entry {
	padding: 12px;
}
.blog-comment .postbithead {
	border: none;
	border-bottom: 1px solid #E4E4E4;
	padding: 0 0 6px;
	background-color: transparent;
}
.blog-comment .postcontrols a {
	color: #3e3e3e !important;
}
.blog-comment .postbithead .postcontrols {
	margin-top: 0;
}
.blog-comment .postbit-chkbox {
	margin-top: 0;
}
#postcomment_heading img {
	top: 2px;
	margin-bottom: 0;
}
#block_custom_page #pagecontent {
	background-color: #ffffff;
	padding: 12px;
	border: 1px solid #E4E4E4;
	line-height: 1.5;
}
#message_list .userprof_headers.userprof_headers_border, .picture_comments .postbithead,
.comment_blockrow.postbit_headers.postbit_borders, #message_list .postbit .postbithead {
	border: none;
	border-bottom:  solid 1px #e4e4e4;
	background-color: transparent;
	padding-left: 0;
	padding-top: 0;
}
#message_list .postbitfoot .postcontrols {
	margin-top: 6px;
}
#message_list .postbit .postbit-chkbox {
	margin-top: 0;
}
#message_list .userprof_headers.userprof_headers_border label, #message_list .userprof_headers.userprof_headers_border .postbit-right {
	padding: 0 0 6px 0;
}

.userprof blockquote {
	padding: 12px 12px 12px 0 !important;
}
#message_form .blockhead img {
	margin-bottom: -2px;
}
#picturecommentpopups {
	top: 16px;
}
span.cke_skin_kama {
	border-radius: 0 !important;
	-moz-border-radius: 0 !important;
	-webkit-border-radius: 0 !important;
	border: solid 1px #e4e4e4 !important;
}
.cke_skin_kama .cke_wrapper, .cke_skin_kama .cke_toolgroup, .cke_skin_kama .cke_dialog_body, .cke_skin_kama .cke_dialog_contents, .cke_skin_kama .cke_dialog_footer {
	border-radius: 0 !important;
	-moz-border-radius: 0 !important;
	-webkit-border-radius: 0 !important;
}
.cke_skin_kama .cke_wrapper {
	background-image: none !important;
}
.comment_blockrow.postbit_headers.postbit_borders .postcontrols {
	margin-top: -10px;
}
.comment_blockrow.postbit_headers.postbit_borders .postcontrols a {
	color: #383838;
}
.cms_comments_page .cms_node_edits_title img {
	margin-bottom: -7px;
}
#node_edits #form_widget_comments .blockfoot.actionbuttons {
	padding-right: 12px;
}
.tborder.vB_DatePicker.page {
	background-color: #ffffff;
}


.printable body {
	width: 100%;
}
.printable .logo-image {
	height: auto !important;
	position: inherit;
}
.printable .above_body {
	background-color: #43A6DF;
	padding: 60px 12px 12px;
}
.searchbits .postbitdetails_noavatar .posthead {
	background-color: #2E3539;
	border-color: #2E3539;
	color: #ffffff;
}
.list_no_decoration li img.inlineimg {
	padding: 0;
}
#no-new-message {
	background-color: #F2F2F2;
	color: #3E3E3E;
	font-size: 14px;
	font-weight: bold;
	padding: 6px 0;
	text-align: center;
	text-transform: none;
}
.threadtitle {
    padding-right: 3px;
}

/* search tabs */

#searchtypeswitcher {
	border-bottom: 3px solid #2E3539;  
}

#searchtypeswitcher li {
	display: inline;
}

#searchtypeswitcher li a {
	display: block;
	padding: 0 12px;
	height: 48px;
	line-height: 48px;
	margin-right: 12px;
	background-color: #43A6DF; 
	float: left;
	clear: right;
	color: #ffffff; 
	text-decoration:none;
}

#searchtypeswitcher li.selected a {
	background-color: #2E3539; 
}

#searchtypeswitcher li a:hover {
	background-color: #43A6DF; 
}
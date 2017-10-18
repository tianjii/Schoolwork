#include <fstream>
#include <iostream>
#include <string>
#include "SongLibrary.h"

//////////////////DO NOT CHANGE THIS CODE////////////////////////

//Construct a Song object with values
Song::Song(const std::string& title, const std::string& artist, 
     const std::string& album, unsigned int year){
	this->title = title;
	this->artist = artist;
	this->album = album;
	this->year = year;
	used = false;
	this->song_group_ptr = NULL;
}

//Song equality doesn't depend on pointers or being used
bool operator== (const Song& s1, const Song& s2){
	return (s1.getYear() == s2.getYear()) && (s1.getTitle() == s2.getTitle())
          && (s1.getAlbum() == s2.getAlbum()) && (s1.getArtist() == s2.getArtist());
}

//Modifier for group pointer
void Song::updateSongGroupPointer(SongGroupNode* ptr){
	if(ptr){
		//Check that ptr is actually for this Song.
		assert(ptr->m_song->value == *this); 
		song_group_ptr = ptr;
	}
	else{
		song_group_ptr = NULL;
	}
}

//Make output easier by overload operator<<
std::ostream& operator<< (std::ostream& ostr, const Song& song){
	if(!song.getSongGroupPointer()){
		ostr << "\"" << song.getTitle() << "\" by " << song.getArtist() << " on \"" 
	       << song.getAlbum() << "\" (" << song.getYear() << ")" << std::endl;
	}
	else{
		ostr << "\"" << song.getTitle() << "\" by " << song.getArtist() << " on \"" 
		<< song.getAlbum() << "\" (" << song.getYear() << ")" << " in Song Group "
		<< song.getSongGroupPointer()->id << std::endl;
	}
	return ostr;
}

/////////////////////////YOUR CODE STARTS HERE////////////////////////////////
//////////////////////////////GROUP FUNCTIONS/////////////////////////////////

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-id is the ID of the list we are searching for
BEHAVIOR:
None
RETURN:
NULL if no list matches the ID, otherwise returns the GroupListNode* containing
the head of the list with ID id.
*/
GroupListNode* GroupExists(GroupListNode* song_groups, GroupID id){
	if (!song_groups) {
		return NULL;
	}
	
	GroupListNode* tmp = song_groups;
		
	//Read through each node, return node if IDs match
		while (tmp != NULL) {
		if (tmp->value->id == id) {
			return tmp;
		}

		tmp = tmp->ptr;
	}
	
	return NULL;
}


/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-id is the ID of the list we are creating
BEHAVIOR:
Add a new song group to song_groups, give the new song group ID id. Order of
song groups is not guaranteed.
RETURN:
None
*/
void MakeGroup(GroupListNode*& song_groups, GroupID id){
	GroupListNode* tmp;
	SongGroupNode* newgroup;

	//If making the first group
	if (!song_groups) {
		song_groups = new GroupListNode;
		tmp = song_groups;
		tmp->ptr = NULL;
		newgroup = new SongGroupNode;
		tmp->value = newgroup;
		newgroup->id = id;
		newgroup->m_song = NULL;
		newgroup->next_song_ptr = NULL;
		newgroup->prev_song_ptr = NULL;
		newgroup->next_by_artist_ptr = NULL;
		newgroup->prev_by_year_ptr = NULL;

		}
	//Usual case, make new group at end of list
	else {
	tmp = song_groups;


	while (tmp->ptr != NULL) {
		tmp = tmp->ptr;
	}
	tmp->ptr = new GroupListNode;
	newgroup = new SongGroupNode;
	tmp->ptr->value = newgroup;
	tmp->ptr->ptr = NULL;
	newgroup->id = id;    
	newgroup->m_song = NULL;
	newgroup->next_song_ptr = NULL;
	newgroup->prev_song_ptr = NULL;
	newgroup->next_by_artist_ptr = NULL;
	newgroup->prev_by_year_ptr = NULL;
	}
}


/*
ARGUMENTS:
-group_head points to the head of a song group
-song is the Song we are checking the group for
BEHAVIOR:
None
RETURN:
If song is found in the group return true. If song is not found,
return false.
*/
bool SongInGroup(SongGroupNode* group_head, const Song& song){
	SongGroupNode* tmp = group_head;
	while (tmp->next_song_ptr != NULL) {
		if (tmp->m_song->value == song) {
			return true;
		}
		tmp = tmp->next_song_ptr;

	}


	return false;

}

/*
ARGUMENTS:
-library_ptr points to the LibraryNode* containing the Song we want to add.
-list_ptr is the head of the song group we want to add the song to.
BEHAVIOR:
Modify the group pointed to by list_ptr to reflect that the song is in the group.
This may change the length of the list. Modifies the Song's members as well.
RETURN:
None
*/
void AddToGroup(LibraryNode* library_ptr, GroupListNode* list_ptr){
	SongGroupNode* grp_tmp1 = list_ptr->value;
	SongGroupNode* grp_tmp2 = list_ptr->value;

	//If the head node is only one in the group (i.e. no songs, that node becomes the first song)
	if (list_ptr->value->m_song == NULL) {
		list_ptr->value->m_song = library_ptr;
		library_ptr->value.setUsedInGroup(true);
		library_ptr->value.updateSongGroupPointer(list_ptr->value);
		list_ptr->value->next_by_artist_ptr = NULL;
		list_ptr->value->prev_by_year_ptr = NULL;
		list_ptr->value->next_song_ptr = NULL;
		list_ptr->value->prev_song_ptr = NULL;


	}

	//Go down linked list until NULL
	else { 
	while (grp_tmp1->next_song_ptr != NULL) {
		grp_tmp1 = grp_tmp1->next_song_ptr;
	}

	grp_tmp1->next_song_ptr = new SongGroupNode;
	grp_tmp2 = grp_tmp1->next_song_ptr;
	grp_tmp2->id = grp_tmp1->id;
	//Insert Song address
	grp_tmp2->m_song = library_ptr;
	library_ptr->value.setUsedInGroup(true);
	library_ptr->value.updateSongGroupPointer(grp_tmp2);

	grp_tmp2->prev_song_ptr = grp_tmp1;
	grp_tmp2->next_song_ptr = NULL;

	grp_tmp2->next_by_artist_ptr = NULL;
	grp_tmp2->prev_by_year_ptr = NULL;

	//Moving packwards in group, if node
	//shares artist set next_by_artist_ptr

	while (grp_tmp1) {
		if (grp_tmp1->m_song->value.getArtist() == grp_tmp2->m_song->value.getArtist()) {
			if (!grp_tmp1->next_by_artist_ptr) {
			grp_tmp1->next_by_artist_ptr = grp_tmp2;
			break;}}

			grp_tmp1 = grp_tmp1->prev_song_ptr;
		}

	grp_tmp1 = grp_tmp2->prev_song_ptr;

	//Move back to find song with an earlier year

	while (grp_tmp1) {
		if (grp_tmp1->m_song->value.getYear() < grp_tmp2->m_song->value.getYear()) {
				grp_tmp2->prev_by_year_ptr = grp_tmp1;
				break;
		}

		grp_tmp1 = grp_tmp1->prev_song_ptr;
	}

	}


}

/*
ARGUMENTS:
-library_ptr points to the LibraryNode* containing the Song we want to remove from a group.
-song_groups points to a singly-linked list of song group heads
BEHAVIOR:
Modifies the Song's member variables to reflect that it is not in a group. Modifies the group
so that the Song is not in the group. This function may cause song_groups to be modified as well.
RETURN:
None
*/
void RemoveFromGroup(LibraryNode* library_ptr, GroupListNode* song_groups){

SongGroupNode* toDelete = library_ptr->value.getSongGroupPointer();
SongGroupNode* tmp;
GroupListNode* list_ptr = song_groups;

library_ptr->value.updateSongGroupPointer(NULL);
library_ptr->value.setUsedInGroup(false);

//Find head node
while(list_ptr->value->id != toDelete->id) {
	list_ptr = list_ptr->ptr;
}


tmp = list_ptr->value;

//If first node in list, set list ptr to 2nd node before deleting
if (toDelete == list_ptr->value) {
	if (toDelete->next_song_ptr != NULL) { 
	list_ptr->value = toDelete->next_song_ptr;
	}

	else {
		toDelete->m_song = NULL;
		return;
	}
}


//Go through all Nodes in Group
while(tmp) {
	if (tmp->next_by_artist_ptr == toDelete) {
		tmp->next_by_artist_ptr = toDelete->next_by_artist_ptr;
	}

	else if (tmp->prev_by_year_ptr == toDelete) {
		tmp->prev_by_year_ptr = toDelete->prev_by_year_ptr;
	}


	if (tmp->next_song_ptr == toDelete) {
		tmp->next_song_ptr = toDelete->next_song_ptr;
	}
	else if (tmp->prev_song_ptr == toDelete) {
		tmp->prev_song_ptr = toDelete->prev_song_ptr;
	}

	tmp = tmp->next_song_ptr;


}
delete toDelete;

}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-list_ptr1 contains to the song group head of Group A
-list_ptr2 contains the song group head of Group B
BEHAVIOR:
Modify Group A so that at the end of its songs, the songs of Group B are added in the same
order they were found in Group B. Remove the now-empty Group B.
RETURN:
None
*/
void CombineGroups(GroupListNode*& song_groups, GroupListNode*& list_ptr1, GroupListNode*& list_ptr2){
	SongGroupNode* grp_tmp1 = list_ptr1->value;
	
	//Traverse to end of song group
	while (grp_tmp1->next_song_ptr != NULL) {
		grp_tmp1 = grp_tmp1->next_song_ptr;
	}

	grp_tmp1->next_song_ptr = list_ptr2->value;
	list_ptr2->value->prev_song_ptr = grp_tmp1;
	

	//Change IDs of newly added songs
	while (grp_tmp1) {
		grp_tmp1->m_song->value.updateSongGroupPointer(grp_tmp1);
		grp_tmp1->id = list_ptr1->value->id;
		grp_tmp1 = grp_tmp1->next_song_ptr;
	}
	
	//Go through list to delete old group
	GroupListNode* tmp1 = song_groups;
	GroupListNode* tmp2;
	while (tmp1 != list_ptr2) {
		tmp2 = tmp1;
		tmp1 = tmp1->ptr;
	}

	tmp2->ptr = tmp1->ptr;
	delete tmp1;


}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-library_ptr points to the LibraryNode* containing the Song we want to remove from a group.
BEHAVIOR:
Remove the group from the list of song groups. No Song objects should remain associated with the
group, and the function should modify Song member variables appropriately to reflect this. Any
memory associated with the group must be released.
RETURN:
None
*/
void RemoveGroup(GroupListNode*& song_groups, GroupListNode* list_ptr){
SongGroupNode* grp_tmp1 = list_ptr->value;
SongGroupNode* grp_tmp2 = grp_tmp1;



//Increment through songs, delete the head song each time
while (grp_tmp2) {
	grp_tmp1 = grp_tmp2;
	grp_tmp1->m_song->value.setUsedInGroup(false);
	grp_tmp1->m_song->value.updateSongGroupPointer(NULL);
	grp_tmp2 = grp_tmp2->next_song_ptr;
	delete grp_tmp1;
} 


//Remove node from group List
GroupListNode* tmp1 = song_groups;
GroupListNode* tmp2;
if (tmp1 == list_ptr) {
	song_groups = list_ptr->ptr;
}
else {
	while (tmp1 != list_ptr) {
		tmp2 = tmp1;
		tmp1 = tmp1->ptr;
	}
		tmp2->ptr = tmp1->ptr;

	}

delete tmp1;

}

/*
ARGUMENTS:
-list_ptr is the head of the song group we want to add the song to.
BEHAVIOR:
Recompute all prev_by_year_ptr members in the song group pointed to by
list_ptr
RETURN:
None
*/

void RecomputePrevByYear(GroupListNode* list_ptr){
SongGroupNode* tmp1 = list_ptr->value;
SongGroupNode* tmp2;
SongGroupNode* foundyr;
unsigned int dist;
unsigned int year1;
unsigned int year2;

bool foundyear;

while (tmp1) { //For every song in group
	tmp2 = tmp1;
	while (!foundyear && tmp2 != NULL) {
		//Start at Group Node, move back to find prev year
		year1 = tmp1->m_song->value.getYear(); 
		year2 = tmp2->m_song->value.getYear();
		if ( year2 < year1 ) { 
			tmp1->prev_by_year_ptr = tmp2;
			break;
		}
		tmp2 = tmp2->prev_song_ptr;
	}
	 //Set pointer, move to next song
	tmp1 = tmp1->next_song_ptr;
	}



}

////////////////////////////PRINT FUNCTIONS////////////////////////////////////

/*
ARGUMENTS:
-library_head points to the first LibraryNode* of the song library
-print_file points to an ostream to print output to
BEHAVIOR:
Print each song in the library in the order it was added.
RETURN:
None
*/
void PrintLibrary(LibraryNode* library_head,std::ostream& print_file){
 LibraryNode* tmp = library_head;
 Song s;
 int num = 0;
 while (tmp != NULL) {
 	s = tmp->value;
 	num+=1;
 	print_file<<"\""<<s.getTitle()<<"\" by "<<s.getArtist()<<" on \""<<s.getAlbum()<<"\" ("<<s.getYear()<<")"<<std::endl;
 	tmp = tmp->ptr;
 }

 print_file<<"Library contains "<<num<<" song(s)"<<std::endl;


}

/*
ARGUMENTS:
-group_head points to the first SongGroupNode* of the group to print
-print_file points to an ostream to print output to
BEHAVIOR:
Print each song in the group in the order it was added.
RETURN:
None
*/
void PrintGroupSequential(SongGroupNode* group_head,std::ostream& print_file){
SongGroupNode* tmp = group_head;

unsigned int id = tmp->id;

print_file<<"List ID "<<id<<" contains:"<<std::endl;
int num = 0;
if (tmp->m_song) {
 while (tmp) {
 	num+=1;
 	print_file<<tmp->m_song->value;
 	tmp = tmp->next_song_ptr;
 }
}

 print_file<<num<<" song(s)"<<std::endl;
}

/*
ARGUMENTS:
-group_ptr points to the location in a particular song group to start printing from
-print_file points to an ostream to print output to
BEHAVIOR:
Print a rewind list by following the prev_by_year_ptr pointers, starting from the song
pointed to by group_ptr.
RETURN:
None
*/
void PrintGroupRewind(SongGroupNode* group_ptr,std::ostream& print_file){
	int num = 0;
	print_file<<"Rewind list for "<<group_ptr->m_song->value.getYear()<<std::endl;
	while (group_ptr) {
		num+=1;
		Song s = group_ptr->m_song->value;
		print_file<<"\t#"<<num<<": "<<s;
		group_ptr = group_ptr->prev_by_year_ptr;
	}


	print_file<<"Rewind list contained "<<num<<" song(s)."<<std::endl;
}

/*
ARGUMENTS:
-group_ptr points to the location in a particular song group to start printing from
-print_file points to an ostream to print output to
BEHAVIOR:
Print a rewind list by following the next_by_artist_ptr pointers, starting from the song
pointed to by group_ptr.
RETURN:
None
*/
void PrintGroupMarathon(SongGroupNode* group_ptr,std::ostream& print_file){
	int num = 0;
print_file<<"Marathon list for "<<group_ptr->m_song->value.getArtist()<<std::endl;
while (group_ptr != NULL) {
		num+=1;
		Song s = group_ptr->m_song->value;
		print_file<<"\t#"<<num<<": "<<s;
		group_ptr = group_ptr->next_by_artist_ptr;
	}

print_file<<"Marathon list contained "<<num<<" song(s)."<<std::endl;

}

/*
ARGUMENTS:
-group_head points to the first SongGroupNode* of the group to analyze
-print_file points to an ostream to print output to
BEHAVIOR:
Find the rewind list with the most songs in the song group pointed to by group_head.
Print the rewind list and the song count to print_file.
RETURN:
None
*/
void PrintLongestGroupRewind(GroupListNode* group_head,std::ostream& print_file){
	SongGroupNode* current1 = group_head->value;
	SongGroupNode* current2 = group_head->value;
	SongGroupNode* placeholder;
	int longest = 0;

//Records Song with longest rewind, points to it with placeholder
	while (current1) {
		int num = 0;
		current2 = current1;
		while (current2) {
			num+=1;
			current2 = current2->prev_by_year_ptr;
		}

		if (num > longest) {
			longest = num;
			placeholder = current1;
		}
		current1 = current1->next_song_ptr;
	}

int num = 0;
print_file<<"Maximum size rewind list is for year "<<placeholder->m_song->value.getYear()<<std::endl;
	while (placeholder) {
		num+=1;
		Song s = placeholder->m_song->value;
		print_file<<"\t#"<<num<<": "<<s;
		placeholder = placeholder->prev_by_year_ptr;
	}


	print_file<<"Longest rewind list contained "<<num<<" song(s)."<<std::endl;





}

///////////////////////////////CLEANUP/////////////////////////////////////////

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
BEHAVIOR:
Delete every group. Do not leak. Modifies all groups and the song_groups list.
Update every Song to reflect not being in a group.
RETURN:
None
*/
void DeleteAllSongGroups(GroupListNode*& song_groups){
GroupListNode* listtmp1 = song_groups;
GroupListNode* listtmp2;
SongGroupNode* head;
SongGroupNode* grouptmp;

//Delete each group
while (listtmp1) {
	head = listtmp1->value;
	//Delete each song group node
	while (head) {
		grouptmp = head;
		head = head->next_song_ptr;
		delete grouptmp;
	}

	listtmp2 = listtmp1;
	listtmp1 = listtmp1->ptr;

	delete listtmp2;

}




}

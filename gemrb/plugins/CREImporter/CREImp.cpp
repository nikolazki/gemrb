/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/CREImporter/CREImp.cpp,v 1.27 2004/04/07 09:54:49 edheldil Exp $
 *
 */

#include "../../includes/win32def.h"
#include "CREImp.h"
#include "../Core/Interface.h"
#include "../../includes/ie_stats.h"

CREImp::CREImp(void)
{
	str = NULL;
	autoFree = false;
}

CREImp::~CREImp(void)
{
	if (str && autoFree) {
		delete( str );
	}
}

bool CREImp::Open(DataStream* stream, bool autoFree)
{
	if (stream == NULL) {
		return false;
	}
	if (str && this->autoFree) {
		delete( str );
	}
	str = stream;
	this->autoFree = autoFree;
	char Signature[8];
	str->Read( Signature, 8 );
	if (strncmp( Signature, "CRE V1.0", 8 ) != 0) {
		if (strncmp( Signature, "CRE V1.2", 8 ) != 0) {
			if (strncmp( Signature, "CRE V2.2", 8 ) != 0) {
				if (strncmp( Signature, "CRE V9.0", 8 ) != 0) {
					printf( "[CREImporter]: Not a CRE File or File Version not supported: %8s\n",
						Signature );
				} else
					CREVersion = IE_CRE_V9_0;
				return true;
			} else
				CREVersion = IE_CRE_V2_2;
			return true;
		} else
			CREVersion = IE_CRE_V1_2;
		return true;
	}
	CREVersion = IE_CRE_V1_0;
	return true;
}

Actor* CREImp::GetActor()
{
	int RandColor = core->LoadTable( "RANDCOLR" );
	TableMgr* rndcol = core->GetTable( RandColor );
	Actor* act = new Actor();
	act->InParty = false;
	unsigned long strref;
	str->Read( &strref, 4 );
	char* poi = core->GetString( strref );
	act->SetText( poi, 0 );
	free( poi );
	str->Read( &strref, 4 );
	poi = core->GetString( strref );
	act->SetText( poi, 1 );
	free( poi );
	str->Read( &act->BaseStats[IE_MC_FLAGS], 2 );
	str->Seek( 2, GEM_CURRENT_POS );
	str->Read( &act->BaseStats[IE_XPVALUE], 4 );
	str->Read( &act->BaseStats[IE_XP], 4 );
	str->Read( &act->BaseStats[IE_GOLD], 4 );
	str->Read( &act->BaseStats[IE_STATE_ID], 4 );
	str->Read( &act->BaseStats[IE_HITPOINTS], 2 );
	str->Read( &act->BaseStats[IE_MAXHITPOINTS], 2 );
	str->Read( &act->BaseStats[IE_ANIMATION_ID], 2 );
	//str->Seek(2, GEM_CURRENT_POS);
	unsigned short tmp;
	str->Read( &tmp, 2 );
	str->Read( &act->BaseStats[IE_METAL_COLOR], 1 );
	str->Read( &act->BaseStats[IE_MINOR_COLOR], 1 );
	str->Read( &act->BaseStats[IE_MAJOR_COLOR], 1 );
	str->Read( &act->BaseStats[IE_SKIN_COLOR], 1 );
	str->Read( &act->BaseStats[IE_LEATHER_COLOR], 1 );
	str->Read( &act->BaseStats[IE_ARMOR_COLOR], 1 );
	str->Read( &act->BaseStats[IE_HAIR_COLOR], 1 );
	/*printf("%d %d %d %d %d %d %d\n", act->BaseStats[IE_METAL_COLOR], 
		act->BaseStats[IE_MINOR_COLOR],
		act->BaseStats[IE_MAJOR_COLOR],
		act->BaseStats[IE_SKIN_COLOR],
		act->BaseStats[IE_LEATHER_COLOR],
		act->BaseStats[IE_ARMOR_COLOR],
		act->BaseStats[IE_HAIR_COLOR]);*/
	if (act->BaseStats[IE_METAL_COLOR] >= 200) {
		act->BaseStats[IE_METAL_COLOR] = atoi( rndcol->QueryField( ( rand() %
			10 ) +
														1,
														act->BaseStats[IE_METAL_COLOR] -
														200 ) );
	}
	if (act->BaseStats[IE_MINOR_COLOR] >= 200) {
		act->BaseStats[IE_MINOR_COLOR] = atoi( rndcol->QueryField( ( rand() %
			10 ) +
														1,
														act->BaseStats[IE_MINOR_COLOR] -
														200 ) );
	}
	if (act->BaseStats[IE_MAJOR_COLOR] >= 200) {
		act->BaseStats[IE_MAJOR_COLOR] = atoi( rndcol->QueryField( ( rand() %
			10 ) +
														1,
														act->BaseStats[IE_MAJOR_COLOR] -
														200 ) );
	}
	if (act->BaseStats[IE_SKIN_COLOR] >= 200) {
		act->BaseStats[IE_SKIN_COLOR] = atoi( rndcol->QueryField( ( rand() %
			10 ) +
														1,
														act->BaseStats[IE_SKIN_COLOR] -
														200 ) );
	}
	if (act->BaseStats[IE_LEATHER_COLOR] >= 200) {
		act->BaseStats[IE_LEATHER_COLOR] = atoi( rndcol->QueryField( ( rand() %
			10 ) +
															1,
															act->BaseStats[IE_LEATHER_COLOR] -
															200 ) );
	}
	if (act->BaseStats[IE_ARMOR_COLOR] >= 200) {
		act->BaseStats[IE_ARMOR_COLOR] = atoi( rndcol->QueryField( ( rand() %
			10 ) +
														1,
														act->BaseStats[IE_ARMOR_COLOR] -
														200 ) );
	}
	if (act->BaseStats[IE_HAIR_COLOR] >= 200) {
		act->BaseStats[IE_HAIR_COLOR] = atoi( rndcol->QueryField( ( rand() %
			10 ) +
														1,
														act->BaseStats[IE_HAIR_COLOR] -
														200 ) );
	}

	unsigned char TotSCEFF;
	str->Read( &TotSCEFF, 1 );
	str->Read( act->SmallPortrait, 8 );
	act->SmallPortrait[8] = 0;
	str->Read( act->LargePortrait, 8 );
	act->LargePortrait[8] = 0;
	str->Read( &act->BaseStats[IE_REPUTATION], 1 );
	str->Read( &act->BaseStats[IE_HIDEINSHADOWS], 1 );
	str->Read( &act->BaseStats[IE_ARMORCLASS], 2 );
	str->Read( &act->Modified[IE_ARMORCLASS], 2 );
	str->Read( &act->BaseStats[IE_ACCRUSHINGMOD], 2 );
	str->Read( &act->BaseStats[IE_ACMISSILEMOD], 2 );
	str->Read( &act->BaseStats[IE_ACPIERCINGMOD], 2 );
	str->Read( &act->BaseStats[IE_ACSLASHINGMOD], 2 );
	str->Read( &act->BaseStats[IE_THAC0], 1 );			//Unknown in CRE V2.2
	str->Read( &act->BaseStats[IE_NUMBEROFATTACKS], 1 );	//Unknown in CRE V2.2
	str->Read( &act->BaseStats[IE_SAVEVSDEATH], 1 );		//Fortitude Save in V2.2
	str->Read( &act->BaseStats[IE_SAVEVSWANDS], 1 );		//Reflex Save in V2.2
	str->Read( &act->BaseStats[IE_SAVEVSPOLY], 1 );		//Will Save in V2.2
	str->Read( &act->BaseStats[IE_SAVEVSBREATH], 1 );		//Unused in V2.2
	str->Read( &act->BaseStats[IE_SAVEVSSPELL], 1 );		//Unused in V2.2
	str->Read( &act->BaseStats[IE_RESISTFIRE], 1 );		
	str->Read( &act->BaseStats[IE_RESISTCOLD], 1 );
	str->Read( &act->BaseStats[IE_RESISTELECTRICITY], 1 );
	str->Read( &act->BaseStats[IE_RESISTACID], 1 );
	str->Read( &act->BaseStats[IE_RESISTMAGIC], 1 );
	str->Read( &act->BaseStats[IE_RESISTMAGICFIRE], 1 );
	str->Read( &act->BaseStats[IE_RESISTMAGICCOLD], 1 );
	str->Read( &act->BaseStats[IE_RESISTSLASHING], 1 );
	str->Read( &act->BaseStats[IE_RESISTCRUSHING], 1 );
	str->Read( &act->BaseStats[IE_RESISTPIERCING], 1 );
	str->Read( &act->BaseStats[IE_RESISTMISSILE], 1 );
	str->Read( &act->BaseStats[IE_DETECTILLUSIONS], 1 );
	str->Read( &act->BaseStats[IE_SETTRAPS], 1 );
	str->Read( &act->BaseStats[IE_LORE], 1 );
	str->Read( &act->BaseStats[IE_LOCKPICKING], 1 );
	str->Read( &act->BaseStats[IE_STEALTH], 1 );
	str->Read( &act->BaseStats[IE_TRAPS], 1 );
	str->Read( &act->BaseStats[IE_PICKPOCKET], 1 );
	str->Read( &act->BaseStats[IE_FATIGUE], 1 );
	str->Read( &act->BaseStats[IE_INTOXICATION], 1 );
	str->Read( &act->BaseStats[IE_LUCK], 1 );
	switch (CREVersion) {
		case IE_CRE_V1_0:
			 {
				str->Read( &act->BaseStats[IE_PROFICIENCYLONGSWORD], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYSHORTSWORD], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYLONGBOW], 1 );	//Generic Bow
				str->Read( &act->BaseStats[IE_PROFICIENCYSPEAR], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYMACE], 1 );		//Blunt Weapons
				str->Read( &act->BaseStats[IE_PROFICIENCYFLAILMORNINGSTAR], 1 );	//Spiked Weapons
				str->Read( &act->BaseStats[IE_PROFICIENCYAXE], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYDART], 1 );		//Missile Weapons
				str->Seek( 13, GEM_CURRENT_POS );
			}
			break;

		case IE_CRE_V1_2:
			 {
				str->Read( &act->BaseStats[IE_PROFICIENCYMARTIALARTS], 1 );	//Fist
				str->Read( &act->BaseStats[IE_PROFICIENCYLONGSWORD], 1 );		//Edged
				str->Read( &act->BaseStats[IE_PROFICIENCYWARHAMMER], 1 );		//Hammer
				str->Read( &act->BaseStats[IE_PROFICIENCYAXE], 1 );			//Axe
				str->Read( &act->BaseStats[IE_PROFICIENCYQUARTERSTAFF], 1 );	//Club
				str->Read( &act->BaseStats[IE_PROFICIENCYLONGBOW], 1 );		//Bow
				str->Seek( 15, GEM_CURRENT_POS );
			}
			break;

		case IE_CRE_V2_2:
			 {
				str->Seek( 13, GEM_CURRENT_POS );
			}
			break;

		case IE_CRE_V9_0:
			 {
				str->Read( &act->BaseStats[IE_PROFICIENCYLONGSWORD], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYSHORTSWORD], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYLONGBOW], 1 );		//Bows
				str->Read( &act->BaseStats[IE_PROFICIENCYSPEAR], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYAXE], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYDART], 1 );			//Missile
				str->Read( &act->BaseStats[IE_PROFICIENCYBASTARDSWORD], 1 );  //Great Sword
				str->Read( &act->BaseStats[IE_PROFICIENCYDAGGER], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYHALBERD], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYMACE], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYFLAILMORNINGSTAR], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYWARHAMMER], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYQUARTERSTAFF], 1 );
				str->Read( &act->BaseStats[IE_PROFICIENCYCROSSBOW], 1 );
				str->Seek( 6, GEM_CURRENT_POS );
			}
			break;
	}
	str->Read( &act->BaseStats[IE_TRACKING], 1 );
	str->Seek( 32, GEM_CURRENT_POS );
	str->Read( &act->StrRefs[0], 100 * 4 );
	str->Read( &act->BaseStats[IE_LEVEL], 1 );
	str->Read( &act->BaseStats[IE_LEVEL2], 1 );
	str->Read( &act->BaseStats[IE_LEVEL3], 1 );
	str->Seek( 1, GEM_CURRENT_POS );
	str->Read( &act->BaseStats[IE_STR], 1 );
	str->Read( &act->BaseStats[IE_STREXTRA], 1 );
	str->Read( &act->BaseStats[IE_INT], 1 );
	str->Read( &act->BaseStats[IE_WIS], 1 );
	str->Read( &act->BaseStats[IE_DEX], 1 );
	str->Read( &act->BaseStats[IE_CON], 1 );
	str->Read( &act->BaseStats[IE_CHR], 1 );
	str->Read( &act->Modified[IE_MORALEBREAK], 1 );
	str->Read( &act->BaseStats[IE_MORALEBREAK], 1 );
	str->Read( &act->BaseStats[IE_HATEDRACE], 1 );
	str->Read( &act->BaseStats[IE_MORALERECOVERYTIME], 1 );
	str->Seek( 1, GEM_CURRENT_POS );
	str->Read( &act->BaseStats[IE_KIT], 4 );
	for (int i = 0; i < 5; i++) {
		char aScript[9];
		str->Read( aScript, 8 );
		aScript[8] = 0;
		if (( stricmp( aScript, "None" ) == 0 ) || ( aScript[0] == '\0' )) {
			act->Scripts[i] = NULL;
			continue;
		}
		act->Scripts[i] = new GameScript( aScript, 0, act->locals );
		act->Scripts[i]->MySelf = act;
	}
	switch (CREVersion) {
		case IE_CRE_V1_2:
			str->Seek( 162, GEM_CURRENT_POS );
			str->Read( &act->BaseStats[IE_TEAM], 1 );
			str->Read( &act->BaseStats[IE_FACTION], 1 );
			break;

		default:
			break;
	}
	str->Read( &act->BaseStats[IE_EA], 1 );
	str->Read( &act->BaseStats[IE_GENERAL], 1 );
	str->Read( &act->BaseStats[IE_RACE], 1 );
	str->Read( &act->BaseStats[IE_CLASS], 1 );
	str->Read( &act->BaseStats[IE_SPECIFIC], 1 );
	str->Read( &act->BaseStats[IE_SEX], 1 );
	str->Seek( 5, GEM_CURRENT_POS );
	str->Read( &act->BaseStats[IE_ALIGNMENT], 1 );
	str->Seek( 4, GEM_CURRENT_POS );
	str->Read( act->scriptName, 32 );

	str->Read( &act->KnownSpellsOffset, 4 );
	str->Read( &act->KnownSpellsCount, 4 );
	str->Read( &act->SpellMemorizationOffset, 4 );
	str->Read( &act->SpellMemorizationCount, 4 );
	str->Read( &act->MemorizedSpellsOffset, 4 );
	str->Read( &act->MemorizedSpellsCount, 4 );
	str->Read( &act->ItemSlotsOffset, 4 );
	str->Read( &act->ItemsOffset, 4 );
	str->Read( &act->ItemsCount, 4 );

	str->Seek( 8, GEM_CURRENT_POS );

	str->Read( act->Dialog, 8 );
	act->BaseStats[IE_ARMOR_TYPE] = 0;
	act->SetAnimationID( ( unsigned short ) act->BaseStats[IE_ANIMATION_ID] );
	/*if(act->anims)
		act->anims->DrawCircle = false;*/

	// Reading inventory
//	act->inventory = new Inventory();

	std::vector<CREItem*> items;
	str->Seek( act->ItemsOffset, GEM_STREAM_START );
	for (size_t i = 0; i < act->ItemsCount; i++) {
		items.push_back( GetItem() );
	}

	str->Seek( act->ItemSlotsOffset, GEM_STREAM_START );
	for (int i = 0; i < INVENTORY_SIZE; i++) {
		ieWord  index;
		str->Read( &index, 2 );

		if (index != 0xFFFF)
			act->inventory.SetSlotItem( items[index], i );
	}
	act->inventory.dump();


	// Reading spellbook
	act->spellbook = new Spellbook();

	std::vector<CREKnownSpell*> known_spells;
	std::vector<CREMemorizedSpell*> memorized_spells;

	str->Seek( act->KnownSpellsOffset, GEM_STREAM_START );
	for (size_t i = 0; i < act->KnownSpellsCount; i++) {
		known_spells.push_back( GetKnownSpell() );
		//act->spellbook->AddKnownSpell( GetKnownSpell() );
	}

	str->Seek( act->MemorizedSpellsOffset, GEM_STREAM_START );
	for (size_t i = 0; i < act->MemorizedSpellsCount; i++) {
		memorized_spells.push_back( GetMemorizedSpell() );
		//act->spellbook->AddMemorizedSpell( GetMemorizedSpell() );
	}

	str->Seek( act->SpellMemorizationOffset, GEM_STREAM_START );
	for (size_t i = 0; i < act->SpellMemorizationCount; i++) {
		CRESpellMemorization* sm = GetSpellMemorization();

		for (int j = 0; j < known_spells.size(); j++) {
			CREKnownSpell* spl = known_spells[j];
			if (spl->Type == sm->Type and spl->Level == sm->Level)
				sm->known_spells.push_back( spl );
		}
		for (int j = 0; j < sm->MemorizedCount; j++) {
			sm->memorized_spells.push_back( memorized_spells[sm->MemorizedIndex + j] );
		}
		act->spellbook->AddSpellMemorization( sm );
	}

	act->spellbook->dump();



	act->Init(); //applies effects, updates Modified
	return act;
}

CREKnownSpell* CREImp::GetKnownSpell()
{
	CREKnownSpell* spl = new CREKnownSpell();

	str->Read( &spl->SpellResRef, 8 );
	str->Read( &spl->Level, 2 );
	str->Read( &spl->Type, 2 );

	return spl;
}

CRESpellMemorization* CREImp::GetSpellMemorization()
{
	CRESpellMemorization* spl = new CRESpellMemorization();

	str->Read( &spl->Level, 2 );
	str->Read( &spl->Number, 2 );
	str->Read( &spl->Number2, 2 );
	str->Read( &spl->Type, 2 );
	str->Read( &spl->MemorizedIndex, 4 );
	str->Read( &spl->MemorizedCount, 4 );

	return spl;
}

CREMemorizedSpell* CREImp::GetMemorizedSpell()
{
	CREMemorizedSpell* spl = new CREMemorizedSpell();

	str->Read( &spl->SpellResRef, 8 );
	str->Read( &spl->Flags, 4 );

	return spl;
}

CREItem* CREImp::GetItem()
{
	CREItem *itm = new CREItem();

	str->Read( itm->ItemResRef, 8 );
	str->Read( &itm->Unknown08, 2 );
	str->Read( &itm->Usages[0], 2 );
	str->Read( &itm->Usages[1], 2 );
	str->Read( &itm->Usages[2], 2 );
	str->Read( &itm->Flags, 4 );

	return itm;
}

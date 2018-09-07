#include <iostream>
#include <map>
#include <nana/gui.hpp>

using namespace nana;

// The categories that can be serched for

enum class eCat
{
    drawings,
    instructions,
    data,
    test
};

class cSearchFolders
{
public:

    cSearchFolders()
    {
        // specify folders that need to be searched for each category
        Add("./drawings",eCat::drawings);
        Add("./drawings/extras", eCat::drawings );
    }

    /** Add to folders that will be searched
        @param[in] patch to folder
        @param[in] cat search category
    */
    void Add( const std::string& path, eCat cat )
    {
        myFolders.insert( std::pair< int, std::string >( (int)cat, path ) );
    }

    /** Add a category to be searched */
    void Add( eCat cat )
    {
        mySearchCats.push_back( cat );
    }

    void Clear()
    {
        mySearchCats.clear();
    }
    /** Folders that need to be searched
        @return vector of folder paths
    */
    std::vector< std::string > Folders()
    {
        std::vector< std::string > vfolder;

        // loop over categories to be searched
        for( eCat cat : mySearchCats )
        {
            // loop over folders in category
            auto ret = myFolders.equal_range( (int)cat );
            for ( auto it=ret.first; it!=ret.second; ++it)
            {
                // save folder path to return vector
                vfolder.push_back( it->second );
            }
        }
        return vfolder;
    }

private:

    std::multimap< int, std::string > myFolders;
    std::vector< eCat > mySearchCats;
};

int main()
{
    try
    {
        form fm;
        inputbox inbox(fm,"","WADE ANTENNA SEARCH TOOL");
        inputbox::boolean s_drawings("Search Drawings",false);
        inputbox::boolean s_instructions("Search Instructions",false);
        inputbox::boolean s_sheets("Search Data Sheets",false);
        inputbox::boolean s_tests("Search Test Data",false);
        inputbox::text target("Search for","");

        if( ! inbox.show( s_drawings, s_instructions, s_sheets, s_tests, target  ) )
            exit(1);

        cSearchFolders SearchFolders;
        if( s_drawings.value() )
            SearchFolders.Add( eCat::drawings );

        std::vector< std::string > vFolders = SearchFolders.Folders();

        msgbox msg("Folders to be searched");
        for( auto f : vFolders )
        {
            msg << "Searching " << f << "\n";
        }
        msg.show();


        //exec();
    }
    catch( std::runtime_error& e )
    {
        msgbox mb( e.what() );
        mb();
    }
}


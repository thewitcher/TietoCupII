#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../BotClient/helper.h"

class TestTest : public QObject
{

    Q_OBJECT
    
public:
    TestTest();
    
private Q_SLOTS:
    void decodeTest0();
};

TestTest::TestTest()
{
}

void TestTest::decodeTest0()
{
    char signal[] = "4\n2 2 2\n3 3 1\nB 2 2\t3 3\t4 4\nB 2 1\t5 5\t6 6\n";

    ReceivedSignalData rcData = Helper::decodeSignal( signal );

    QCOMPARE( rcData.rowsCount, 4 );
    QCOMPARE( ( int ) rcData.moves.size(), 2 );

    QCOMPARE( rcData.moves.at( 0 ).row, 2 );
    QCOMPARE( rcData.moves.at( 0 ).column, 2 );
    QCOMPARE( rcData.moves.at( 0 ).who, 2 );
    QCOMPARE( rcData.moves.at( 1 ).row, 3 );
    QCOMPARE( rcData.moves.at( 1 ).column, 3 );
    QCOMPARE( rcData.moves.at( 1 ).who, 1 );

    QCOMPARE( ( int ) rcData.basePoint.size(), 2 );

    multimap< int, vector< pair< int, int > > >::iterator it = rcData.basePoint.begin();

    QCOMPARE( it->first, 1 );
    QCOMPARE( it->second.at( 0 ).first, 5 );
    QCOMPARE( it->second.at( 0 ).first, 5 );

    QCOMPARE( it->second.at( 1 ).first, 6 );
    QCOMPARE( it->second.at( 1 ).first, 6 );

    it++;

    QCOMPARE( it->first, 2 );
    QCOMPARE( it->second.at( 0 ).first, 3 );
    QCOMPARE( it->second.at( 0 ).first, 3 );

    QCOMPARE( it->second.at( 1 ).first, 4 );
    QCOMPARE( it->second.at( 1 ).first, 4 );
}

QTEST_APPLESS_MAIN(TestTest)

#include "tst_testtest.moc"

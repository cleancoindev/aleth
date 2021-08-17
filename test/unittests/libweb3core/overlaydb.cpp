// Aleth: Ethereum C++ client, tools and libraries.
// Copyright 2015-2019 Aleth Authors.
// Licensed under the GNU General Public License, Version 3.

#include <libdevcore/DBFactory.h>
#include <libdevcore/OverlayDB.h>
#include <libethereum/Block.h>
#include <libethereum/BlockChain.h>
#include <libethereum/ChainParams.h>
#include <libethereum/GenesisInfo.h>
#include <test/tools/libtesteth/BlockChainHelper.h>
#include <test/tools/libtesteth/TestHelper.h>
#include <sstream>
#include <fstream>
#include <string>
//#include <nlohmann/json.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace dev;
using namespace db;
using namespace dev::db;
using namespace dev::eth;
using namespace dev::test;
namespace utf = boost::unit_test;
//using json = nlohmann::json;

TEST(OverlayDB, basicUsage)
{
    std::unique_ptr<db::DatabaseFace> db = DBFactory::create(DatabaseKind::MemoryDB);
    ASSERT_TRUE(db);

    OverlayDB odb(std::move(db));
    EXPECT_TRUE(!odb.get().size());

    // commit nothing
    odb.commit();

    string const value = "\x43";
    EXPECT_TRUE(!odb.get().size());

    odb.insert(h256(42), &value);
    EXPECT_TRUE(odb.get().size());
    EXPECT_TRUE(odb.exists(h256(42)));
    EXPECT_EQ(odb.lookup(h256(42)), value);

    odb.commit();
    EXPECT_TRUE(!odb.get().size());
    EXPECT_TRUE(odb.exists(h256(42)));
    EXPECT_EQ(odb.lookup(h256(42)), value);

    odb.insert(h256(41), &value);
    odb.commit();
    EXPECT_TRUE(!odb.get().size());
    EXPECT_TRUE(odb.exists(h256(41)));
    EXPECT_EQ(odb.lookup(h256(41)), value);
}

TEST(OverlayDB, auxMem)
{
    std::unique_ptr<db::DatabaseFace> db = DBFactory::create(DatabaseKind::MemoryDB);
    ASSERT_TRUE(db);

    OverlayDB odb(std::move(db));

    string const value = "\x43";
    bytes valueAux = fromHex("44");

    odb.insert(h256(42), &value);
    odb.insert(h256(0), &value);
    odb.insert(h256(numeric_limits<u256>::max()), &value);

    odb.insertAux(h256(42), &valueAux);
    odb.insertAux(h256(0), &valueAux);
    odb.insertAux(h256(numeric_limits<u256>::max()), &valueAux);

    odb.commit();

    EXPECT_TRUE(!odb.get().size());

    EXPECT_TRUE(odb.exists(h256(42)));
    EXPECT_EQ(odb.lookup(h256(42)), value);

    EXPECT_TRUE(odb.exists(h256(0)));
    EXPECT_EQ(odb.lookup(h256(0)), value);

    EXPECT_TRUE(odb.exists(h256(std::numeric_limits<u256>::max())));
    EXPECT_EQ(odb.lookup(h256(std::numeric_limits<u256>::max())), value);

    EXPECT_TRUE(odb.lookupAux(h256(42)) == valueAux);
    EXPECT_TRUE(odb.lookupAux(h256(0)) == valueAux);
    EXPECT_TRUE(odb.lookupAux(h256(std::numeric_limits<u256>::max())) == valueAux);
}

TEST(OverlayDB, rollback)
{
    std::unique_ptr<db::DatabaseFace> db = DBFactory::create(DatabaseKind::MemoryDB);
    ASSERT_TRUE(db);

    OverlayDB odb(std::move(db));
    bytes value = fromHex("42");

    odb.insert(h256(43), &value);
    EXPECT_TRUE(odb.get().size());
    odb.rollback();
    EXPECT_TRUE(!odb.get().size());
}

TEST(OverlayDB, readNBlocks)
{
//    std::ifstream i("file.json");
//    json j;
//    i >> j;
}

TEST(OverlayDB, insertWitness)
{
    std::unique_ptr<db::DatabaseFace> db = DBFactory::create(DatabaseKind::MemoryDB);
    ASSERT_TRUE(db);

//    OverlayDB odb(std::move(db));
//
//    EXPECT_TRUE(!odb.get().size());
//    auto hash = "sdlfkdslfk";
//    std::ifstream infile(hash);
//    std::string line;
//
//    while (std::getline(infile, line))
//    {
//        std::istringstream iss(line);
//        std::string key;
//        std::string value;
//
//        std::getline(iss, key, ',');
//        std::getline(iss, value, ',');
//        bytes valueBytes = fromHex(value);
//        odb.insertAux(h256(key), &valueBytes);
//
//        EXPECT_TRUE(odb.lookupAux(h256(key)) == valueBytes);
//    }

//    TestBlock genesis = TestBlockChain::defaultGenesisBlock();
//    TestBlockChain bc(genesis);
//
//    BlockChain& bcRef = bc.interfaceUnsafe();
    //    Block block;
    //    block.enact(&(VerifiedBlockRef some), bc);
    //
    //    block.enact(&(VerifiedBlockRef some), wrapper)
    //    struct wrapper {
    //        blockchain
    //        overlaydb
    //    };
    //    - Modify the Block::enact;
}

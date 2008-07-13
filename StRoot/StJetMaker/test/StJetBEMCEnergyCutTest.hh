// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef STJETBEMCENERGYCUTTEST_HH
#define STJETBEMCENERGYCUTTEST_HH

#include <cppunit/extensions/HelperMacros.h>

class StJetBEMCEnergyCutTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( StJetBEMCEnergyCutTest );
  CPPUNIT_TEST( testEnergy );
  CPPUNIT_TEST( testStatus );
  CPPUNIT_TEST( testAdc );
  CPPUNIT_TEST( testTowerId2006 );
  CPPUNIT_TEST( testTowerId2005 );
  CPPUNIT_TEST( testTowerId2003 );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testEnergy();
  void testStatus();
  void testAdc();
  void testTowerId2006();
  void testTowerId2005();
  void testTowerId2003();

private:

  std::set<int> get2003TowerIdSet();

  const static int _2003TowerIdList[];
};

#endif // STJETBEMCENERGYCUTTEST_HH

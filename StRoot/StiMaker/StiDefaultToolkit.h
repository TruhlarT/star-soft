/** 
 * @file  StiDefaultToolkit.h
 * @brief Default Implementation of the StiToolkit Abstract interface
 * @author Claude A Pruneau, Wayne State University, 
 * @date   March 2001
 * @copyright 2001, STAR  Experiment at BNL, All rights reserved.  
 *  
 * Permission to use, copy, modify and distribute this software and its
 * documentation strictly for non-commercial purposes is hereby granted 
 * without fee, provided that the above copyright notice appears in all
 * copies and that both the copyright notice and this permission notice
 * appear in the supporting documentation. The authors make no claims 
 * about the suitability of this software for any purpose. It is     
 * provided "as is" without express or implied warranty.             
 */
#ifndef StiDefaultToolkit_H
#define StiDefaultToolkit_H 1
#include "Sti/StiToolkit.h"
#include "StiMaker/RootEditableParameter.h"

/** 
 * @class StiDefaultToolkit
 * @brief Definition of toolkit
 */
class StiDefaultToolkit : public StiToolkit
{
public:
  
  StiDefaultToolkit() ;
  virtual Factory<StiHit>          * getHitFactory();
  virtual Factory<StiKalmanTrack>  * getTrackFactory();
  virtual Factory<StiMcTrack>      * getMcTrackFactory();
  virtual Factory<StiDetector>      * getDetectorFactory();
  virtual Factory<StiCompositeTreeNode<StiDetector> >  * getDetectorNodeFactory();
  virtual Factory<StiKalmanTrackNode>   * getTrackNodeFactory();
  virtual Factory<EditableParameter>    * getParameterFactory();
  virtual Factory<Filter<StiTrack>  >  * getTrackFilterFactory();

  // common object containers
  virtual StiMasterDetectorBuilder * getDetectorBuilder();
  virtual StiDetectorContainer     * getDetectorContainer();
  virtual StiHitContainer          * getHitContainer();
  virtual StiHitContainer          * getMcHitContainer();
  virtual StiTrackContainer        * getTrackContainer();
  virtual StiTrackContainer        * getMcTrackContainer();
  
  // service and convenience class objects.
  virtual StiDetectorFinder      * getDetectorFinder();
  virtual StiTrackSeedFinder          * getTrackSeedFinder();
  virtual StiTrackFinder         * getTrackFinder();
  virtual StiTrackFitter         * getTrackFitter();
  virtual StiTrackMerger         * getTrackMerger();
  virtual StiVertexFinder        * getVertexFinder();
  virtual StiHitLoader<StEvent,StMcEvent,StiDetectorBuilder> * getHitLoader();
  virtual StAssociationMaker     * getAssociationMaker();
  virtual void setAssociationMaker(StAssociationMaker * a);
  virtual void add(StiDetectorGroup<StEvent,StMcEvent>* detectorGroup);

  //RootEditableParameter & getParameters();
  void setGuiEnabled(bool );
  bool isGuiEnabled() const;
  void setMcEnabled(bool);
  bool isMcEnabled() const;
  void setEvaluatorEnabled(bool);
  bool isEvaluatorEnabled() const;
  
 protected:
  
  bool _guiEnabled;
  bool _evaluatorEnabled;
  bool _mcEnabled;
  
  virtual ~StiDefaultToolkit();
  
  // small object factories
  Factory< Filter<StiTrack>  > * _trackFilterFactory;
  Factory<EditableParameter>   * _parameterFactory;
  Factory<StiHit>              * _hitFactory;
  Factory<StiKalmanTrack>      * _trackFactory;
  Factory<StiMcTrack>          * _mcTrackFactory;
  Factory<StiDetector>         * _detectorFactory;
  Factory< StiCompositeTreeNode<StiDetector> > * _detectorNodeFactory;
  Factory<StiKalmanTrackNode>                  * _trackNodeFactory;
  
  // common object containers 
  StiMasterDetectorBuilder     * _detectorBuilder;
  StiDetectorContainer         * _detectorContainer;
  StiHitContainer              * _hitContainer;
  StiHitContainer              * _mcHitContainer;
  StiTrackContainer            * _trackContainer;
  StiTrackContainer            * _mcTrackContainer;
  
  // service and convenience class objects.
  StiDetectorFinder       * _detectorFinder;
  StiTrackSeedFinder      * _trackSeedFinder;
  StiTrackFinder          * _trackFinder;
  StiTrackFitter          * _trackFitter;
  StiTrackMerger          * _trackMerger;
  StiVertexFinder         * _vertexFinder;
  StiHitLoader<StEvent,StMcEvent, StiDetectorBuilder> * _hitLoader;
  StAssociationMaker                       * _associationMaker; 
};

#endif



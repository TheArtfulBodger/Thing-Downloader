import * as React from 'react';
import LinkCountBar from '../components/LinkCountBar';
import CurrentlyDownloading from '../components/CurrentlyDownloading';
import Page from '../components/Page';

import { Heading } from '@primer/react';
import JobQueue from '../components/JobQueue';

const IndexPage = () => {
  return (
    <Page bc={[['/', 'Thing Downloader'], ['/jobs', 'Jobs'], ['/jobs', 'Jobs In Progress']]}>
    <Heading>Downloadables & Queue</Heading>
      <LinkCountBar page="active"/>
      <CurrentlyDownloading/>
      <JobQueue/>
      </Page>
  );
};

export default IndexPage;

export const Head = () => <title>Home Page</title>;

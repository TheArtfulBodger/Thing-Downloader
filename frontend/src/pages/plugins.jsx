import * as React from 'react';
import PluginList from '../components/Plugins';
import Page from '../components/Page';

import { Heading } from '@primer/react';

const IndexPage = () => {
  return (
    <Page bc={[['/', 'Thing Downloader'], ['/plugins', 'Plugins']]}>
      <Heading>Plugins</Heading>
      <PluginList />
    </Page>
  );
};

export default IndexPage;

export const Head = () => <title>Plugins</title>;

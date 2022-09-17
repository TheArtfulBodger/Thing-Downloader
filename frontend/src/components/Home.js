import React from 'react';
import { BaseStyles, PageLayout } from '@primer/react';
import Downloadables from './Downloadables';
import PageHeader from './PageHeader';

const Home = () => {
  return (
    <BaseStyles>
<PageHeader/>
<PageLayout>
  <PageLayout.Content>
  <Downloadables/>
  </PageLayout.Content>

</PageLayout>
  </BaseStyles>
  );
};

export default Home;

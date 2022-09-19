import React from 'react';
import { Box, ProgressBar, Text, Label, Heading, CounterLabel, StateLabel } from '@primer/react';

import Others from './Downloadables/Others';
import DownloadableContainer from './Downloadables/DownloadableContainer';
import CurrentlyDownloading from './Downloadables/CurrentlyDownloading';

function Downloadables(props) {
  return (<>
    <Box p={4} mx={8}>
      <Heading>Downloadables & Queue</Heading>
      <Others />
      <CurrentlyDownloading/>
      <DownloadableContainer/>
    </Box>
  </>
  );
}

export default Downloadables;

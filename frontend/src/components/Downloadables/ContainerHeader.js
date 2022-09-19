import React from 'react';
import { Client } from 'rpc-websockets';
import { Box, ProgressBar, Text, Label, Heading, CounterLabel, StateLabel } from '@primer/react';

import Collapsible from 'react-collapsible';

export default function ContainerHeader (props) {
  return <Box borderTopLeftRadius={10} borderTopRightRadius={10} borderColor="border.default" borderWidth={1} borderStyle="solid" p={2} backgroundColor="canvas.inset">
      <Text fontWeight="bold">{props.children}</Text></Box>;
}

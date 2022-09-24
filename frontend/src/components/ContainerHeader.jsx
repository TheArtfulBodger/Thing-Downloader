import React from 'react';
import { Box, Text } from '@primer/react';

export default function ContainerHeader(props) {
  return (<Box
    borderTopLeftRadius={10} borderTopRightRadius={10} borderColor="border.default"
    borderWidth={1} borderStyle="solid" p={2}
    backgroundColor="canvas.inset"
          >
    <Text fontWeight="bold">{props.children}</Text>
  </Box>);
}

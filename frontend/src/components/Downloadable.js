import React from 'react';
import { Box, ProgressBar, Text, Label, StateLabel } from '@primer/react';

function ProgressPane (props) {
  switch (props.data.status) {
    case '_downloading':
      return (<Box sx={{ width: '300px', float: 'right' }}><Text as="p" m={0} sx={{ textAlign: 'center' }} >{props.data.log}</Text><ProgressBar progress={props.data.progress}/></Box>);

    case '_completed':
      return (<StateLabel status="issueClosed" sx={{ float: 'right', backgroundColor: 'success.emphasis' }}>Downloaded</StateLabel>);
    case '_skipped':
      return (<StateLabel status="issueClosed" sx={{ float: 'right' }}>Skipped</StateLabel>);
    case '_failed':
      return (<StateLabel status="issueClosedNotPlanned" sx={{ float: 'right', backgroundColor: 'danger.emphasis' }}>Failed</StateLabel>);
    default:
      return (<></>);
  }
}

export default function Downloadable (props) {
  return (<Box borderColor="border.default" borderWidth={1} borderStyle="solid" p={4} key={props.data.key}>
        <Text as="span" fontWeight="bold" mx={2}>{props.data.name}</Text>

        <ProgressPane data={props.data}/>
        <br/>
        <Label size="large">{props.data.plugin}</Label>
      </Box>);
}

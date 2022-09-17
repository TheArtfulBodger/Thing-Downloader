import React from 'react';
import { ThemeProvider } from '@primer/react';

import Home from './Home';

const App = () => {
  return (<>
      <ThemeProvider>
          <Home />
    </ThemeProvider>
    </>);
};

export default App;
